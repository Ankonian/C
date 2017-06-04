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
//# include "queue.h" // causes errors. 

# define BUFSIZE 100
# define MAGIC_NUMBER 0xdeadd00d
# define CONSTANT 4 // how many spaces to print for printTree().

// darrell's code:
static inline void spaces(int c)
{
	for(int i = 0; i < c; i+=1)
	{
		printf(" ");
	}
	return;
}
// prints the tree in order.
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
int main(int argc, char **argv)
{
	int c;
	char *inputFileName = "";
	char *outputFileName = "";
	bool verboseMode = false; // this enables verbose mode.
	bool printTree1 = false; // this prints out the tree read in.	
	while((c = getopt(argc, argv, "pvi:o:")) != -1)
	{
		switch(c)
		{
			case 'i':
				inputFileName = strdup(optarg);
				break;
			case 'o':
				outputFileName = strdup(optarg);
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
	if(strlen(inputFileName) == 0)
	{
		input = STDIN_FILENO;
	}
	else
	{
		// Open read only.
		input = open(inputFileName, O_RDONLY);
	}
	if(input < 0) // error handling.
	{
		printf("Could not open file. Exiting now.\n");
		// plug memory leaks.
		free(inputFileName);
		if(strlen(outputFileName))
		{
			free(outputFileName);
		}
		exit(errno);
	}
	// open the output file. if no input file, use stdin
	int output;
	if(strlen(outputFileName) == 0)
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
			if(strlen(inputFileName))
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
		
		if(strlen(inputFileName))
		{
			// only close input if it's not stdin_fileno.
			free(inputFileName);
			close(input);
		}
		if(strlen(outputFileName))
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
	int a = read(input, savedTree, treeSize);
	if(a == 0) // error handling.
	{
		printf("Error reading in tree.\n");
		exit(errno);
	}
	
	// read the tree in from savedTree
	treeNode *root = loadTree(savedTree, treeSize); 	

	// 1 byte at a time, read in what character
	uint8_t in;
	uint64_t bytesCounted = 0;
	treeNode *current = root;
	// read in 1 byte at a time.
	// when you find a character in the tree, increment bytesCounted.
	// when you reach the original fileSize, stop reading.
	// the remaining bits are not counted at all. doing so would be wrong.
	while(bytesCounted < sourceBytes)
	{
		read(input, &in, sizeof(in)); // read in one byte at a time.
		for(uint8_t j = 0; j < 8; j++)
		{
			// the file is read backwards, but bytes are read forward.
			// e.g.:
			// 01001100 11100100 bytes:
			// 76543210 FEDCBA98 order (0 is first, F is last)
			// step through the tree for each byte read 
			uint32_t code = (in & (1 << j) ) >> j; 
			int32_t x = stepTree(root, &current, code);
			// if something is found while stepping through the tree,
			// write it to the output.
			// only write 8 bytes at a time. 
			if(x != -1) 
			{
				// write only 8 bytes
				write(output, &x, sizeof(char)); 
				// increase the bytes counted, then compare it to source bytes.
				// if it's been reached, then stop reading.
				if(++bytesCounted == sourceBytes)
				{
					break;
				}
			}
		}
	}
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
	if(strlen(inputFileName))
	{
		free(inputFileName);
		close(input); // if input is stdin, then don't close it.
	}
	if(strlen(outputFileName))
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
