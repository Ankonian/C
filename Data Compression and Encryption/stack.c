# include <stdio.h>
# include "stack.h"

// The stack.c code was generously donated by Darrell Long on Piazza and I didn't know he donated it so I implemented most of it while thinking about how many other ways I can kill myself
stack *newStack()
{
	stack *s;
	s->size = 10;
	s->top = 0;
	s->entries = (item *)calloc(s->size, sizeof(item));
	return s;
}

void delStack(stack *s)
{
	free(s->entries);
	free(s);
}

item pop(stack *s)
{
	if(empty(s))
	{
		printf("The stack has nothing");
	}
	s->top -= 1;
	return s->entries[s->top];
}
void push(stack *s, item i)
{
	if(full(s))
	{
		s->entries = realloc(s->size*2, sizeof(item));
	}
	entries[s->top] = i;
	s->top++;
	return;
}

bool empty(stack *s)
{
	return (s->size == 0);
}

bool full(stack *s)
{
	return(s->top == s->size);
}
