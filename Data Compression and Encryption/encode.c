# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "huffman.h"
# include "queue.h"

# ifndef MAX
# define MAX 10
# endif

int main(int argc, char **argv)
{

	// My testing code 

	uint64_t test[9] = {2,3,5,6,1,4,8,9,7};
	
	// Testing Histogram
	uint64_t histogram[256] = {0};
	histogram[0] = 1;
	histogram[255] = 1;
	for(uint32_t i = 0; i < 9; i++)
	{
	  histogram[test[i]]++;
	}
	for(uint32_t i = 0; i < 256; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	for(uint32_t i = 0; i < 256; i++)
	{
		printf("%lu ", histogram[i]);
	}
	printf("\n");

	// Testing Huffman treeNode and join function
	treeNode *t1 = newNode('a', true, 3);
	treeNode *t2 = newNode('b', true, 1);
	treeNode *t3 = newNode('c', true, 2);
	treeNode *t4 = join(t1, t2);
	printTree(t1, 1);
	printTree(t2, 1);
	printTree(t3, 1);
	printTree(t4, 2);
	
	//Testing the priority queue
	queue *q = newQueue(4);
	enqueue(q, 3);
	enqueue(q, 7);
	enqueue(q, 6);
	printQueue(q);
	printf("\n");
	item i;
	dequeue(q, &i);
	printf("%d\n", i);
	


	// Code from William
	int c;
	bool verboseMode = false;
	bool printTree1 = false;
	char *inputFile = "";
	char *outputFile = "";
	while((c = getopt(argc, argv, "pvi:o:")) != -1)
	{
		switch(c)
		{
			case 'v':
				verboseMode = true;
				break;
			case 'i':
				inputFile = strdup(optarg);
				break;
			case 'o':
				outputFile = strdup(optarg);
				break;
			case 'p':
				printTree1 = true;
				break;
		}
	}
	int input;
	if(strlen(inputFile))
	{
		input = open(inputFile, O_RDONLY);
		if(input < 0)
		{
			printf("Error opening input file.\n");
			free(inputFile);
			if(strlen(outputFile))
			{
				free(outputFile);
			}
			return 1;
		}
	}
	int output;
	if(strlen(outputFile))
	{
		output = open(outputFile, O_WRONLY | O_APPEND | O_CREAT, 0666);

		if(output < 0)
		{
			printf("Error opening or creating file.\n");//write(2, "ASS\n", 4);
			free(outputFile);
			if(strlen(inputFile))
			{
				free(intputFile);
			}
		}
	}
	else
	{
		output = STD_FILENO;
	}
	if(printTree1)
	{
		printf("Print tree here.\n");
	}
	if(verboseMode)
	{
		printf("Verbose mode turned on.\n");
	}
	uint32_t magicNumber = 0xDeadD00d;
	uint64_t bytes = 0;

	//code table[256];
	uint32_t histogram[256];
	for(int i = 0; i < 256; i++)
	{
		histogram[i] = 0;
	}
	// necessary conditions to prevent bugs.
	histogram[0]+=1;
	histogram[255]+=1;
	//code s;
	uint64_t size = 8;
	char *arse = calloc(size, sizeof(char));
	int n = 0; 
	char in;
	while(read(input, &in, sizeof(char)) != 0)
	{
		histogram[(uint8_t) in] += 1;
		bytes +=1;
		arse[n++] = in;
		if(n == size)
		{
			size *= 2;
			char *t = arse;
			arse = realloc(arse, size*sizeof(char));
			if(arse == NULL)
			{	
				free(t);
				printf("Too big.\n");
				exit(0);
			}
		}
		
	}
	//printf("%s", arse);
	queue *countQueue = newQueue(256);
	uint16_t treeBytes = 0;  
	for(uint16_t i = 0; i < 256; i++)
	{
		/*
		if(isgraph(i))
		{
			printf("%c: %d\n", i, histogram[i]);
		}
		else {
			printf("0x%02x: %d\n", i, histogram[i]);
		}
		*/
		if(histogram[i] > 0)
		{
			bool isLeaf = 1;
			treeNode *leaf = newNode(i, isLeaf, histogram[i]);
			enqueue(countQueue, leaf);
			treeBytes += 2; // each leaf needs 2 bytes: 1 for 'L', 1 for symbol.
		}
	}
	treeNode *root;
	while(!emptyQ(countQueue))
	{
		treeNode *r, *l;
		dequeue(countQueue, &r);
		dequeue(countQueue, &l);
		// once the last two nodes are on the queue, pop them, and make it the thing.
		if(!emptyQ(countQueue))
		{
			treeNode *i = join(l, r);
			enqueue(countQueue, i);
		}
		else
		{
			// if the queue is empty , the root is the last thing.
			root = join(l, r);
		}
		treeBytes+=1;
	}
	//printTree(root,1);
	
	code s = newCode();
	code table[256]; //= malloc(sizeof(code)*256);
	for(int i = 0; i < 256; i++)
	{
		table[i] = newCode();
	}
	buildCode(root, s, table);
	printTree(root, 1);
	s = table[(uint8_t) '0'];
	if(emptyCode(&s))
		printf("\'0\' is empty.\n");
	while(!emptyCode(&s))
	{
		uint32_t code;
		popCode(&s, &code);
		printf("%d", code);
	}	
	delQueue(countQueue);
	// start writing.
	
	write(output, &magicNumber, sizeof(magicNumber));
        write(output, &bytes, sizeof(bytes));
	write(output, &treeBytes, sizeof(treeBytes));
	dumpTree(root, output);

	//printf("%s\n" ,arse);	
	uint64_t i = 0;
	uint8_t path = 0;
	while(i < bytes)
	{
		code temp = table[(uint8_t)arse[i]];
		//uint8_t path = 0;
		uint8_t j = 0;
		while(!emptyCode(&temp))
		{
			uint32_t code;
			popCode(&temp, &code);
			path |=((code << (j % 8)) >> (j % 8));
			if(j % 8 == 7)
			{
				write(output, &path, sizeof(path));
				path = 0;
			}
			j++;
		}
		i++;
	}
	if(verboseMode)
	{
		printf("Source Bytes: %" PRIu64 "\n", bytes);
		printf("Tree Bytes: %d\n", treeBytes); 	
	}	
	if(printTree1)
	{
		printTree(root, 1);
	}
	delTree(root);	
	if(strlen(inputFile))
	{
		close(input);
		free(inputFile);
	}
	if(strlen(outputFile))
	{
		close(output);
		free(outputFile);
	}

	return 0;
}
