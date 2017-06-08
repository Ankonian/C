# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <inttypes.h>

# include "code.h"
# include "queue.h"
# include "huffman.h"
# include "bv.h"

# define READSIZE 1024
# define CONSTANT 4
# define DEBUG 0

void printCode(code s); // for debugging.
void printBinary(uint8_t x);// prints an 8 bit number in binary (for debugging)
// from darrell's code.
static inline void spaces(int c); // prints c spaces. (for print tree).
void printTree(treeNode *t, int depth); // prints out the tree. specify depth to fit your screen size.

int main(int argc, char **argv)
{
	int c;
	bool verboseMode = false;
	bool printTree1 = false;
	// prevents multiple strlen() calls.
	bool hasInputName = false;
	bool hasOutputName = false;
	char *inputFile = "";
	char *outputFile = "";
	// options:
	// -v: verbose: turns on statistics gathered for this decoding.
	// -i: input: specifies an input file. default is stdin.
	// -o: output: specifies an output file. default is stdout.
	// -p: prints out the tree.
	while((c = getopt(argc, argv, "pvi:o:"))!= -1)
	{
		switch(c)
		{
			case 'v':
				verboseMode = true;
				break;
			case 'i':
				inputFile = strdup(optarg);
				hasInputName = true;
				break;
			case 'o':
				outputFile = strdup(optarg);
				hasOutputName = true;
				break;
			case 'p':
				printTree1 = true;
				break;
		}
	}
	// input: 
	// if we specified an input name, open it. put in error handling.
	// if not, take in from standard input.
	int input;
        if(hasInputName)
        {
                input = open(inputFile, O_RDONLY);
		// error handling.
                if (input < 0)
                {
                        printf("Error opening input file.\n");
                        free(inputFile);
                        if(hasOutputName)
                        {
                                free(outputFile);
                        }
                        return 1;
                }
        }
	else
	{
		input = STDIN_FILENO;
	}
	// output:
	// if we specified a name, open it. if it's not there, create it.
	// file permissions: 0666 means everyone can open it.
	// if not, write to STDOUT.
	int output;
	if(hasOutputName)
	{
		output = open(outputFile, O_WRONLY | O_APPEND | O_CREAT, 0666);
		// error handling.
		if (output < 0) {
			printf("Error opening or creating file.\n");
			free(outputFile);
			if(hasInputName)
			{
				free(inputFile);
			}
			return 1;
		}
	}
	else
	{
		output = STDOUT_FILENO;
	}

	uint32_t magicNumber = 0xdeadd00d;				
	uint64_t bytes = 0;
	uint64_t encodeBytes = 0;

	// initialize histogram.
	uint32_t histogram[256];
	for(int i = 0; i < 256; i++)
	{
		histogram[i] = 0;
	}
	// necessary conditions to prevent bugs.
	histogram[0]+=1;
	histogram[255]+=1;
	
	// since we can't read in from STDIN twice, we have a buffer specifically for it.	
	char readIn[READSIZE];

	char *inputBuffer;
	if(input == STDIN_FILENO)
	{ 
		inputBuffer = calloc(READSIZE, sizeof(char));
	}
	uint64_t sizeOfBuffer = READSIZE;
	int readBytes = read(input, readIn, READSIZE);
	while(readBytes > 0)
	{
		for(int i = 0; i < readBytes; i++)
		{
			// for as many bytes as was read:
			// 1.) increase the histogram's count at that byte's position by 1
			// 2.) save the byte into a buffer, while simultaneously 
			// 3.) incrase bytes read.
			histogram[ (uint8_t) readIn[i]] += 1;
			if(input == STDIN_FILENO)
			{
				inputBuffer[bytes] = readIn[i];
			}
			bytes++;
			// if there's not enough space, double the size.
			
			if(bytes == sizeOfBuffer && input == STDIN_FILENO)
			{
				sizeOfBuffer *= 2;
				char *t = inputBuffer; // temp variable
				inputBuffer = realloc(inputBuffer, sizeOfBuffer*sizeof(char));
				if(inputBuffer == NULL)
				{
					// error handling.
					printf("Too big.\n");
					free(t);
					if(hasInputName)
					{
						free(inputFile);
					}
					if(hasOutputName)
					{
						free(outputFile);
					}
					return 1;
				}
			} // end error handling.
			
		} // end for statement.
		// read in the next 1024 bytes.
		readBytes = read(input, readIn, READSIZE);
	}

	// create the tree.
	queue *countQueue = newQueue(256);
	uint16_t treeBytes = 0;  
	uint16_t leafCount = 0;
	for(uint16_t i = 0; i < 256; i++)
	{
		if(histogram[i] > 0)
		{
			// for each byte type that appears in the file, 
			// create a leaf for it; it has a symbol of i, is a leaf, and
			// 	gets the count from the histogram.
			// put it in the priority queue.
			// the priority queue is sorted by count.
			// the largest count is dequeued first. 
			bool isLeaf = 1;
			treeNode *leaf = newNode(i, isLeaf, histogram[i]);
			enqueue(countQueue, leaf);
			leafCount += 1; // for statistics later.
			// each leaf needs 2 bytes: 1 for 'L', 1 for symbol.
			treeBytes += 2;
		}
	}
	treeNode *root; // the final root.
	while(!emptyQ(countQueue))
	{
		treeNode *r, *l;
		dequeue(countQueue, &r);
		dequeue(countQueue, &l);
		// once the last two nodes are on the queue, pop them, and make it the root.
		if(!emptyQ(countQueue))
		{
			treeNode *i = join(l, r);
			enqueue(countQueue, i);
		}
		else
		{
			// if the queue is empty , the root is the last node.
			// the while loop will finish itself.
			root = join(l, r);
		}
		// for every internal node created, treeBytes is increased by 1.
		// 1 byte for 'I' to be written in dumpTree() later.
		treeBytes += 1;
	}
	
	// build the code.
	// initialize every code to 0. 
	code s = newCode();
	code table[256];
	for(int i = 0; i < 256; i++)
	{
		table[i] = newCode();
	}
	// see huffman.c for details.
	buildCode(root, s, table);
	
	// debugging code.
	if(DEBUG)
	{
		printTree(root, 1);
		for(uint16_t i = 0; i != 256; i++)
		{
			if(histogram[i] > 0)
			{
				if(isgraph(i)) {
					printf("\n\nbitvector for \'%c\':\n", i);
				} else {
					printf("\n\nbitvector for 0x%02x:\n", (uint8_t) i);
				}
				printCode(table[(uint8_t) i]);	
			}
		}
	}
	
	// delete the queue.
	if(!emptyQ(countQueue))
	{
		// error handling.
		printf("WARNING! QUEUE NOT EMPTY. MEMORY LEAKS WILL OCCUR.\n");
	}
	delQueue(countQueue);	
	
	// write the magic number, the source bytes, and the tree bytes.
	write(output, &magicNumber, sizeof(magicNumber));
    write(output, &bytes, sizeof(bytes));
	write(output, &treeBytes, sizeof(treeBytes));
	encodeBytes += 4 + 8 + 2 + treeBytes;

	// write the tree to the the file.
	// see huffman.c for details.
	dumpTree(root, output);
	
	// write the bits.

	// example:
	// if the path is ABCDE;
	// the order it's popped out of is reversed.
	// order popped out: EDCBA;
	// so, to combat this, I devised a method.
	//
	// I don't increase k. I increase the 
	//
	// bitV:
	// ******** l = 5; k = 0; Abit(bitV, l)
	// **F***** l = 4; k = 0; Bbit(bitV, l); 
	// **FED*** l = 2; k = 0;
	// **FEDCBA
	//
	// next one:
	// path is XYZ
	// order popped out: ZYX
	//
	// *YXFEDCBA
	// ZYXFEDCBA
	//
	// read from decode as:
	// 
	// ABCDEF XYZ
	
	uint64_t i = 0; // where i'm at in the byte buffer.
	uint64_t bitCount = 0; // bitcount.
	uint64_t size = 0xffffffff; // 2 ^ 32 - 1;
	bitV *bitVector = newVec(size);
	if(DEBUG)
	{
		printf("max size: %" PRIu64 "\n", size);
		printf("my size: %" PRIu64 "\n", bytes);
	}
	if(input != STDIN_FILENO)
	{
		lseek(input, 0, SEEK_SET); // go back to beginning.
	}
	while(i < bytes)
	{
		uint8_t byteRead;
		if ( input == STDIN_FILENO)
		{
			byteRead = inputBuffer[i];
		}
		else if (read(input, &byteRead, sizeof(byteRead)) < 1)
		{
			break;
		}
		code temp = table[byteRead];
		uint32_t bit; // for popping.
		uint32_t codeLength = 0;
		// iterate backwards through the path.
		while(popCode(&temp, &bit))
		{	
			if(bit == 0)
			{
				clrBit(bitVector, bitCount + temp.l);
			}
			else if (bit == 1)
			{
				setBit(bitVector, bitCount + temp.l);
			}
			codeLength++;
		}
		bitCount+=codeLength;
		i++;
	}
	// write each byte in bitV to memory in order.
	// write the bitCount * 8. we want bytes. 
	write(output, bitVector->vector, bitCount*8);
	
	// garbage collection.
	delVec(bitVector);
	// verbose statistics.
	if(verboseMode)
	{
		float percentage = 100*encodeBytes/bytes;
		printf("Original %" PRIu64 " bits: leaves %d (%d bytes) ", bytes*8, leafCount, treeBytes);
		printf("encoding %" PRIu64 " bits (%f %%).\n", encodeBytes*8, percentage); 	
	}
	// Print out the tree if you want.
	if(printTree1)
	{
		printTree(root, 1);
	}
	// garbage collection.
	delTree(root);	
	if(input == STDIN_FILENO)
	{
		free(inputBuffer);
	}
	if(hasInputName)
	{
		close(input);
		free(inputFile);
	}
	if(hasOutputName)
	{
		close(output);
		free(outputFile);
	}
	return 0;
}


void printCode(code s)
{
        for(uint32_t i = 0; i < s.l; i++)
        {
                uint32_t x = ((0x1 << (i % 8)) & s.bits[i / 8] ) >> (i % 8);
                printf("%d", x);

        }
        printf("\n");
        return;
}
//prints an 8 bit number in binary (for debugging)
void printBinary(uint8_t x)
{
        for(uint8_t i = 7; i != 0; i--)
        {
                printf("%d", (x >> i) & 0x1 );
	}              
        printf(" ");
        return;
}



static inline void spaces(int c)
{
        for(int i = 0; i < c; i+=1)
        {
                printf(" ");
        }
        return;
}
void printTree(treeNode *t, int depth)
{
        if(t && t->leaf)
        {
                if(isgraph(t->symbol))
                {
                        spaces(CONSTANT*depth);
                        printf("'%c' (%" PRIu64 ")\n", t->symbol, t->count);
                }
                else
                {
                        spaces(CONSTANT*depth);
                        printf("0x%X (%" PRIu64 ")\n", t->symbol, t->count);
                }
        }
        else if (t)
        {
                printTree(t->left, depth + 1);
                spaces(CONSTANT*depth);
                printf("$ (%" PRIu64 ")\n", t->count);
                printTree(t->right, depth + 1);
        }
        else
        {
                //  if it finds a null pointer, it prints it out. You should not have these.
                spaces(CONSTANT*depth);
                printf("NIL POINTER HERE.\n");
        }
        return;
}
