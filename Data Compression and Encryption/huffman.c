# include <stdio.h>
# include <ctype.h>
# include "huffman.h"
# include "code.h"
# include "stack.h"

treeNode *newNode(uint8_t s, bool l, uint64_t c)
{
	// Code
	treeNode *t = (treeNode *)malloc(sizeof(treeNode));
	t->symbol = s;
	t->leaf = l;
	t->count = c;
	return t;
}


treeNode *delTree(treeNode *t)
{
	// Code
	treeNode *u = (treeNode *)malloc(sizeof(treeNode));
	free(t);
	return u;
}
/*
void dumpTree(treeNode *t, int file)
{
	// Code
	// If the node is a leaf, write the leaf to file
	uint8_t buffer[4096];
	if(t->leaf)
	{
		int w = write(file, buffer, 4096);
	}
	// If the node is an interior node, recursively call dumpTree until met a leaf node
	// Arjun suggest this concept
	else
	{
		dumpTree(t->left);
		dumpTree(t->right);
	}
}

treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes)
{
	// Code
}

int32_t *stepTree(treeNode *root, treeNode *t, uint32_t code)
{
	// Code
}

void buildCode(treeNode *t, code s, code table[256])
{
	// Code
	if(t->leaf)
	{
		for(uint32_t i = 0; i < s->l; i++)
		{
			s->bits[i] = 
}
*/
treeNode *join(treeNode *l, treeNode *r)
{
	// Code
	uint64_t count = 0;
	if(l != NIL)
	{
		count += l->count;
	}
	if(r != NIL)
	{
		count += r->count;
	}
	uint8_t symbol = '$';
	bool leaf = false;
	treeNode *t = newNode(symbol, leaf, count);
	t->left = l;
	t->right = r;
	return t;

}

// Debugger function provided by Darrell Long
void printTree(treeNode *t, int depth)
{
	if(t && t->leaf)
	{
		if(isalnum(t->symbol))
		{
			spaces(4 * depth);
			printf("%c (%lu)\n", t->symbol, t->count);
		}
		else
		{
			spaces(4 * depth);
			printf("%x(%lu)\n", t->symbol, t->count);
		}
	}
	else if(t)
	{
		spaces(4 * depth);
		printf("$ (%lu)\n", t->count);
		printTree(t->left, depth + 1);
		printTree(t->right, depth + 1);
	}
	return;
}
