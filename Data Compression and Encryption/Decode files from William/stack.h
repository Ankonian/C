# ifndef _STACK_H
# define _STACK_H
# include <stdint.h>
# include <stdbool.h>
# include "huffman.h"

//# define INVALID 0xDeadD00d

//typedef uint32_t item;

# define INVALID (void *) 0
typedef  treeNode *item;

typedef struct stack
{
	uint32_t size; // how big
	uint32_t top;  // top
	item *entries;
} stack;

stack *newStack();
void delStack(stack *);

item pop(stack *);
void push(stack *, item);

bool empty(stack *);
bool full(stack *);

#endif
