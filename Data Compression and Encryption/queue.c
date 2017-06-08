# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "queue.h"

queue *newQueue(uint32_t size)
{
	queue *q = (queue *)malloc(sizeof(queue));
	q->size = size;
	q->head = 0;
	q->tail = 0;
	q->Q = (item *) calloc(size, sizeof(item));
	return q;
}

void delQueue(queue *q)
{
	free(q->Q);
	free(q);
	return;
}

bool emptyQ(queue *q)
{
	return q->tail == 0;
}

bool fullQ(queue *q)
{
	return q->tail == q->size;
}

bool enqueue(queue *q, item i)
{
	if(fullQ(q))
	{
		return false;
	}
	else
	{
		//Priority queue suggested and modified by Arjun
		if(emptyQ(q))
		{
			q->Q[q->tail++] = i;
		}
		else
		{
			for(int32_t j = 1; ((int32_t)q->tail) - j + 1 >= 0; j++)
			{
				// i <= q->Q[q->tail->j]
				// compare(l, r): return (l - r);
				//if(q->tail - j + 1 == 0 || i->count <= q->Q[q->tail-j]->count)
				if(q->tail - j + 1 == 0 || compare(i, q->Q[q->tail-j]) < 0)
				{
					q->Q[q->tail-j+1] = i;
					break;
				}
				else
				{
					q->Q[q->tail-j+1] = q->Q[q->tail-j];
				}
			}
			q->tail=q->tail + 1;
		}
		return true;
	}
}

bool dequeue(queue *q, item *i)
{
	if(emptyQ(q))
	{
		return false;
	}
	else
	{
		// Pass whatever is at the tail of the queue to item
		*i = q->Q[q->tail-1];
		q->tail = (q->tail-1) % q->size;
		return true;
	}
}

// Debugger function
void printQueue(queue *q)
{
	printf("Print: tail=%d head=%d size=%d\n", q->tail, q->head, q->size);
	for(uint32_t i = q->head; i != q->tail; i = (i + 1) % q->size)
	{
		printf("%c\n", q->Q[i]->symbol);
	}
	return;
}
