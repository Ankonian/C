# include "stack.h"
# include <stdio.h>
# include <stdlib.h>

# define NIL (void *) 0
# define MIN_STACK 10
// looking at Darrell's code
stack *newStack()
{
	stack *s = (stack *) malloc(sizeof(stack));
	s->size = MIN_STACK;
	s->top = 0;
	s->entries = calloc(MIN_STACK, sizeof(item));
	return s;
}

void delStack(stack *s)
{
	free(s->entries);
	free(s);
	return;
}

item pop (stack *s)
{
	if(s->top == 0)
	{
		return INVALID;
	}
	s->top -= 1;
	return s->entries[s->top];
}

void push(stack *s, item a)
{
	if(s->size == s->top)
	{
		// double the size if not big enoufh.
		s->size *= 2;
		s->entries = (item *) realloc(s->entries, s->size * sizeof(item));
	}
	s->entries[s->top] = a;
	s->top += 1;
	return;	
}

bool empty(stack *s)
{
	return s->top == 0; 
}

bool full(stack *s)
{
	if(s->top == s->size)
	{
		return true;
	}
	else
	{
		return false;
	}
	// is always false.
}
