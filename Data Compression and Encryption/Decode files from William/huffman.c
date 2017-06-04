# include "huffman.h"
# include "code.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <inttypes.h>
# include "stack.h"
# include <ctype.h>

/* treeNode's members:
 * 
 * uint8_t symbol
 * uint64_t count;
 * bool leaf;
 * treeNode *left;
 * treeNode *right;
 *
 */
treeNode *newNode(uint8_t s, bool l, uint64_t c)
{
	treeNode *n = malloc(sizeof(treeNode));
	n->symbol = s;
	n->count = c;
	n->leaf = l;
	n->left = NIL;
	n->right = NIL;
	// will not assume leftNode and rightNode pointers for now.
	return n;
}
// Dump a tree onto a file.
void dumpTree(treeNode *t, int file)
{
	// my interpretation:
	// if you start at the top:
	if(t->leaf)
	{
		// if you have a node with $, write to file like this: L $
		write(file, "L", 1); 
		char c[1];
		c[0] = (char) t->symbol; 
		write(file, c, 1);	 
	}
	else // if interior node
	{ 
		// do a post-order traversal.
		dumpTree(t->right, file);
		dumpTree(t->left, file);
		write(file, "I", 1);
	}
}

// Build a tree from the saved tree.
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes)
{
	treeNode *root;
	stack *treeNodePoints = newStack();
	uint16_t i = 0;
	while(i < treeBytes)
	{
		// iterate through all the bytes.
		// if L is read, read in the next byte, and make that the symbol.
		// if I is read, pop the 2 nodes, and join it.
		// otherwise, it's not a tree.
		uint8_t typeOfNode = savedTree[i];
		bool leaf = (typeOfNode == 'L');
		if(leaf)
		{
			i++; // next byte.
			uint8_t symbol = savedTree[i];
			uint64_t count = 0; // just to make it eer to read.
			treeNode *l = newNode(symbol, leaf, count);
			push(treeNodePoints, l);
		}
		else if(typeOfNode == 'I')
		{
			treeNode *right = pop(treeNodePoints);
			treeNode *left = pop(treeNodePoints);
			treeNode *interior = join(left, right);
			push(treeNodePoints, interior);
		} 
		else
		{
			printf("ERROR READING TREE!\n");
			exit(1);
		}
		i++; // next byte.
	}
	// at the end, the last thing on the stack will be the root.
	root = pop(treeNodePoints);
	
	if(empty(treeNodePoints)) // error checking.
	{
		delStack(treeNodePoints);
	}
	else
	{
		// throws a warning if the stack isn't empty. this means you missed some nodes.
		printf("WARNING: STACK NOT EMPTY BEFORE DELETING AT LOADTREE().\n");
		delStack(treeNodePoints);
	}
	return root;
}
// step through a tree following the code
int32_t stepTree(treeNode *root, treeNode **t, uint32_t code)
{
	// pass in 1 bit at a time. check if it's 1 or 0.
	// 1 -> right
	// 0 -> left
	// **t represents a pointer to a pointer to a treeNode. 
	// to access that pointer to a treeNode, use the *t operator.
	// will modify it in decode.c.
	if(code)
	{
		(*t) = (*t)->right;
	}
	else
	{
		(*t) = (*t)->left;
	}
	
	if(*t == NIL) // error checking.
	{
		(*t) = root;  // just a failsafe in case we have null pointers.
		return -1;
	}
	// return the symbol if a leaf is detected, and return to the surface.
	// otherwise, go again.
	// returning -1 tells decode.c to read the next bit.
	// returning a positive number reads a better shit.
	if((*t)->leaf)
	{
		int32_t num = (*t)->symbol; // save the number to return it.
		(*t) = root;
		return num;
	}
	else
	{
		return -1;
	}

}
// Parse a Huffman tree to build codes.
void buildCode(treeNode *t, code s, code table[256])
{
	if(t->leaf)
	{
		for(int i = 0; i < 255; i++)
		{
			uint32_t k;
			table[i] = s;
			popCode(&s, &k);
		}
	}
	return;	
}

void *delTree(treeNode *t)
{
	// postoorder traversal deletion.
	// delete the two trees before you free the node.
	if(t->left != NIL)
	{
		delTree(t->left);
	}	
	if(t->right != NIL)
	{
		delTree(t->right);
	}
	delNode(t);
	return NIL;
}

treeNode *join(treeNode *l, treeNode *r)
{
	uint64_t count = 0;
	if(l != NIL) // error checking
	{
		count += l->count;
	}
	if(r != NIL) // error checking.
	{
		count += r->count;
	}
	bool leaf = false; // is not a leaf.
	uint8_t symbol = 0; // has no symbol.
	treeNode *j = newNode(symbol, leaf, count); // has no symbol, has children, is an addition of frequencies.
	// make the left and right pointers equal to the arguments.
	j->left = l;
	j->right = r;
	return j;
}
