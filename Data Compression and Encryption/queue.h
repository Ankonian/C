# ifndef _QUEUE_H
# define _QUEUE_H
# include <stdint.h>
# include <stdbool.h>
# include "huffman.h"

typedef treeNode *item;

typedef struct queue
{
	uint32_t size;	     // how big?
	uint32_t head, tail; // front and rear locations
	item *Q; // an array to hold queue
} queue;

queue *newQueue(uint32_t size);
void delQueue(queue *q);

bool emptyQ(queue *q);
bool fullQ(queue *q);

bool enqueue(queue *q, item i);
bool dequeue(queue *q, item *i);

# endif

