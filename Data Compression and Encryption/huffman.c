# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <inttypes.h>
# include <ctype.h>

# include "code.h"
# include "huffman.h"
# include "stack.h"

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
	if(n) // error handling.
	{
		n->symbol = s;
		n->count = c;
		n->leaf = l;
		n->left = NIL;
		n->right = NIL;
		// will not assume leftNode and rightNode pointers for now.
	}
	return n;
}
// Dump a tree onto a file.
void dumpTree(treeNode *t, int file)
{
	// dumpTree is called from the root in main.
	// @param: root
	// @param: file descriptor to write to.
	// if a leaf is reached, write L, then its symbol. 
	// example: L$.
	// otherwise, it must be an interior node.
	// dump the tree of both the left and right branches, then write an I.
	// This tells loadTree() to pop the stack twice, and join the two together.
	if(t == NIL) // error handling.
	{
		printf("ERROR DUMPING TREE.\n");
		exit(1);
	}
	if(t->leaf)
	{
		write(file, "L", 1);  // only write 1 byte.
		write(file, &(t->symbol), sizeof(char)); // only write 1 byte.
	}
	else // if it's an interior node.
	{ 
		// do a post-order traversal.
		dumpTree(t->left, file);
		dumpTree(t->right, file);
		write(file, "I", 1); // only write 1 byte.
	}
}

// Build a tree from the saved tree.
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes)
{
	treeNode *root; // return this one.
	stack *treeNodePoints = newStack();
	uint16_t i = 0;
	while(i < treeBytes)
	{
		// iterate through all the bytes.
		// if L is read, read in the next byte, and make that the symbol. Then push to stack.
		// if I is read, pop the 2 nodes, and join it. Then push to stack.
		// otherwise, it's not a tree, and your file is invalid.
		uint8_t typeOfNode = savedTree[i];
		bool leaf = (typeOfNode == 'L');
		if(leaf)
		{
			i++; // Read next byte. This byte is the symbol.
			uint8_t symbol = savedTree[i];
			uint64_t count = 0; // just to make it easier to read.
			treeNode *l = newNode(symbol, leaf, count);
			push(treeNodePoints, l); // push to stack.
		}
		else if(typeOfNode == 'I')
		{
			treeNode *right = pop(treeNodePoints);
			treeNode *left = pop(treeNodePoints);
			// pop 2 nodes, and join them. This is the interior node.
			treeNode *interior = join(left, right);
			push(treeNodePoints, interior);
		} 
		else
		{
			printf("ERROR READING TREE!\n");
			exit(1);
		}
		i++; // next byte. Check if this byte if I
	}
	// at the end, the last thing on the stack will be the root.
	root = pop(treeNodePoints);
	
	if(!empty(treeNodePoints)) // error checking.
	{
		// throws a warning if the stack isn't empty. this means you missed some nodes.
		printf("WARNING: STACK NOT EMPTY BEFORE DELETING AT LOADTREE().\n");
	}
	delStack(treeNodePoints); // garbage collection.
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
	
	if(*t == NIL) // error handling.
	{
		(*t) = root;  // just a failsafe in case we have null pointers.
		printf("ERROR! HIT A NULL NODE WHILE STEPPING THROUGH THE TREE!\n");
		return -1;
	}
	// return the symbol if a leaf is detected, and return to the surface.
	// otherwise, go again.
	// returning -1 tells decode.c to read the next bit.
	// returning a positive number tells decode.c to
	// 	write the symbol to the output file.
	if((*t)->leaf)
	{
		// save the number, return to the root in the tree, and return the number.
		int32_t num = (*t)->symbol;
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
	// @param: root of the treee
	// @param: a blank code
	// @param: an array of codes. array of 256 to represent all possible byte combos.
	// a code will represent a pathway through the node.
	// example: if a path through a node is represented by:
	// ABCDEF
	// where A is the first direction you go, and F is the last direction, 
	// then the code's stack looks like this:
	// FEDCBA
	// Where F is the top of the stack, and A is the bottom of the stack.
	//
	// We are saving it in reverse order.
	//
	// if a leaf is hit, modify the table at its symbol to the current path.
	// the symbol is represented by a byte.
	// 
	// otherwise, we've hit an interior node.
	// push a 0 onto the code stack, then follow the left node.
	// undo changes(pop)
	// push a 1 onto the code stack,  then follow the right node.
	if(t->leaf)
	{
		// modify the table at
		table[t->symbol] = s;
	}	
	else
	{	
		// build the left code stack. 
		pushCode(&s, 0);
		buildCode(t->left, s, table);
		uint32_t k; // placeholder for popCode() to work.
		popCode(&s, &k);
		// build the right code stack.
		pushCode(&s, 1);
		buildCode(t->right, s, table);
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
	uint8_t symbol = '$'; // has a dollar sign for a symbol. always.
	treeNode *interior = newNode(symbol, leaf, count); 
	// has no symbol, has children, is an addition of the child frequencies.
	// make the left and right pointers equal to the arguments.
	// left one has less frequency.
	// right one has more frequency.
	interior->left = l;
	interior->right = r;
	/*
	if(compare(l, r) >= 0)
	{
		interior->left = r;
		interior->right = l;
	}
	else
	{
		interior->left = l;
		interior->right = r;
	}
	*/
	return interior;
}
