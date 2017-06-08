// this is the working code.
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <inttypes.h>
# include <ctype.h>

# include "code.h"
# include "huffman.h"
# include "stack.h"
# include "bv.h" 

# define MAGIC_NUMBER 0xdeadd00d
# define CONSTANT 4 // how many spaces to print for printTree().
# define READSIZE 2048
# define DEBUG 0

// darrell's code:
static inline void spaces(int c); // prints out c spaces.
void printTree(treeNode *t, int depth); // prints the tree in order.
int main(int argc, char **argv)
{
	int c;
	char *inputFileName = "";
	char *outputFileName = "";
	bool verboseMode = false; // this enables verbose mode.
	bool printTree1 = false; // this prints out the tree read in.	
	bool hasInputName = false;
	bool hasOutputName = false;
	while((c = getopt(argc, argv, "pvi:o:")) != -1)
	{
		switch(c)
		{
			case 'i':
				inputFileName = strdup(optarg);
				hasInputName = true;
				break;
			case 'o':
				outputFileName = strdup(optarg);
				hasOutputName = true;
				break;
			case 'v':
				verboseMode = true;
				break;
			case 'p':
				printTree1 = true;
				break;
		}
	}
	// if no file name inputted, input is stdin.
	int input;
	if(hasInputName)
	{
		// Open read only.
		input = open(inputFileName, O_RDONLY);
		if(input < 0) // error handling.
		{
			printf("Could not open file. Exiting now.\n");
			// plug memory leaks.
			free(inputFileName);
			if(hasOutputName)
			{
				free(outputFileName);
			}
			exit(errno);
		}
	}
	else
	{
		input = STDIN_FILENO;
	}	
	// open the output file. if no input file, use stdin
	int output;
	if(!hasOutputName)
	{
		output = STDOUT_FILENO;
	}
	else // open the output file name if there's a name.
	{
		output = open(outputFileName, O_WRONLY | O_APPEND | O_CREAT , 0666);
		if(output < 0) // error handling.
		{
			printf("Could not open or create output file name. Exit.\n");
			// prevent leaks.
			if(hasInputName)
			{
				free(inputFileName);
				close(input);
			}
			free(outputFileName); // free the file name.
			exit(errno);
		}
	}

	// first 4 bytes are the magic number
	uint32_t magicNumber;
	read(input, &magicNumber, sizeof(magicNumber));
	
	// magic number must match, or else it's invalid.	
	if(magicNumber != MAGIC_NUMBER) 
	{
		printf("Invalid file.\n");
		// prevent memory leaks.
		
		if(hasInputName)
		{
			// only close input if it's not stdin_fileno.
			free(inputFileName);
			close(input);
		}
		if(hasOutputName)
		{
			// only close output if it's not stdout_fileno.
			free(outputFileName);
			close(output);
		}
		exit(errno);
	}
	
	// read in 8 bytes. those 8 bytes comprise the uncompressed file size.	
	uint64_t sourceBytes;
	read(input, &sourceBytes, sizeof(sourceBytes));
	
	// read in 2 bytes. those two bytes comprise the size of the tree.
	uint16_t treeSize;
	read(input, &treeSize, sizeof(treeSize));

	// read in the tree (size of treeSize)
	uint8_t savedTree[treeSize];
	uint16_t readTree = read(input, savedTree, treeSize);
	if(readTree != treeSize) // error handling.
	{
		printf("Error reading in tree.\n");
		exit(errno);
	}
	
	// read the tree in from savedTree
	treeNode *root = loadTree(savedTree, treeSize); 	
	if(DEBUG)
	{
		printTree(root,1);
	}
	// 1 byte at a time, read in what character
	uint8_t in[READSIZE];
	uint64_t bytesCounted = 0;
	treeNode *current = root;
	// read in 1 byte at a time.
	// when you find a character in the tree, increment bytesCounted.
	// when you reach the original fileSize, stop reading.
	// the remaining bits are not counted at all. doing so would be wrong.
	uint32_t bytesRead = read(input, in, READSIZE);
	uint64_t placeinBV = 0;
	bitV *readingVector = newVec(sourceBytes);
	while(bytesRead > 0)
	{
		//uint32_t bytesRead = read(input, in, READSIZE);
		//bool sourceBytesReached = false;
		for(uint32_t i = 0; i < bytesRead; i++)
		{
			for(uint8_t j = 0; j < 8; j++)	
			{
				uint32_t code = (in[i] & (1 << j)) >> j; 
				if(code)
				{
					setBit(readingVector, placeinBV);	
				}
				else
				{
					clrBit(readingVector, placeinBV);
				}
				placeinBV++;
			}
		}
		bytesRead = read(input, in, READSIZE);
	}
	uint64_t i = 0; 
	uint8_t writeBuffer[READSIZE];
	uint64_t k = 0;
	while(bytesCounted < sourceBytes )
	{
		int32_t x = stepTree(root, &current, valBit(readingVector, i++));
		if(x != -1)
		{
			writeBuffer[k % READSIZE] = (uint8_t) x;
			k++;
			if(k == READSIZE)
			{
				write(output, writeBuffer, sizeof(writeBuffer));
				k = 0;
			}
			// write(output, &x, sizeof(char));
			bytesCounted++;
		}
	}
	// leftover bytes.
	if(k != 0)
	{
		for(uint64_t j = 0; j < k; j++)
		{
			write(output, &writeBuffer[j], sizeof(char));
		}
	}
	delVec(readingVector); 

	// print the tree here if -p is enabled.
	if(printTree1)
	{
		printf("\n\n\n");
		printTree(root, 1);
	}
	// print statistics gathered.
        if(verboseMode)
        {
                printf("Original %" PRIu64 " bits: ", 8*sourceBytes);
                printf("tree (%d)\n", treeSize);  
        }
	
	// delete the tree.
	delTree(root);
	
	// output file name is optional. we don't have to have it.
	if(hasInputName)
	{
		free(inputFileName);
		close(input); // if input is stdin, then don't close it.
	}
	if(hasOutputName)
	{
		free(outputFileName); 
		close(output);// if output is stdout, then don't close it.
	}
	
	// error handling.
	if(input < 0 || output < 0)
	{
		printf("ERROR CLOSING FILE.\n");
		return 1;
	}
	return 0;
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
                /*  if it finds a null pointer, it prints it out. You should not have these.*/
                spaces(CONSTANT*depth);
                printf("NIL POINTER HERE.\n");
        }
        return;
}
