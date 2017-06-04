# ifndef _HUFFMAN_H
# define _HUFFMAN_H
# include <stdint.h>
# include <stdbool.h>
# include "code.h"
# include <stdlib.h>

# ifndef NIL
# define NIL (void *) 0
# endif

typedef struct DAH treeNode;

struct DAH
{
	uint8_t symbol;
	uint64_t count;
	bool leaf;
	treeNode *left, *right;
};

// newNode, with symbols, leaf or not, and a count associated withit.
treeNode *newNode(uint8_t s, bool l, uint64_t c);

// Dump a Huffman tree onto a file.
void dumpTree(treeNode *t, int file);

// build a tree from the saved tree
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes);

// step through a tree following the code..
int32_t stepTree(treeNode *root, treeNode **t, uint32_t code);

// parse a huffman tree following the code.
void buildCode(treeNode *t, code s, code table[256]);

void *delTree(treeNode *t);

static inline void delNode(treeNode *h) { free(h); return; }

static inline int8_t compare(treeNode *l, treeNode *r)
{
	return l->count - r->count;
}

treeNode *join(treeNode *l, treeNode *r);
# endif
