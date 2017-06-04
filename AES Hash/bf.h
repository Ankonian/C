# ifndef NIL
# define NIL
# endif
# ifndef _BF_H
# define _BF_H
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "aes.h"

// Each function has its own hash function, determined by the salt.
typedef struct bloomf 
{
	uint8_t *v;	//vector
	uint32_t l;	//length
	uint32_t s[4];	//salt
}bloomF;

//static int realLength(int l);

uint32_t hashBF(bloomF *bf, const char *key);


//create a new Bloom Filter of a given length

static inline bloomF *newBF(uint32_t l, uint32_t salt[4])
{
	// Code
	bloomF *bf = malloc(sizeof(bloomF));
	bf->l = l;
	for(uint32_t i = 0; i < 4; i++)
	{
		bf->s[i] = salt[i];
	}
	bf->v = (uint8_t * ) (calloc(1, (l/8)));
	//bf->s = b;
	return bf;
}

// Delete a Bloom filter

static inline void delBF(bloomF *v)
{
	// Code
	free(v->v);
	free(v);
	return;
}

// Return the value of position k in the Bloom Filter

static inline uint32_t valBF(bloomF *x, uint32_t k)
{
	// Code
	uint32_t value = (*(x->v+(k/8)))>>(7-(k%8)) & 1;
  	return value;
}
static inline uint32_t lenBF ( bloomF * x ) { return x -> l ; }

// Count bits in the Bloom filter

static inline uint32_t countBF ( bloomF * b )
{
	// Code
	uint32_t size = 0;
	for(uint32_t i = 0; i < (b->l); i += 1)
	{
		if(b->v[i])
		{
			size++;
		}
	}
	return size;
}

// Set an entry in the Bloom filter

static inline void setBF ( bloomF *x , char * key )
{
	// Code
	uint32_t set = hashBF(x, key);
	uint32_t temp = set % x->l;
	(*(x->v+(temp/8))) |= (1<<(7-temp%8));
}

// Clear an entry in the Bloom filter

static inline void clrBF ( bloomF *x , char * key )
{
	// Code
	uint32_t set = hashBF(x, key);
	uint32_t temp = set % x->l;
	(*(x->v+(temp/8))) &= ~(1<<(7-temp%8));
	return;
}

// Check membership in the Bloom filter

static inline uint32_t memBF ( bloomF *x , const char * key )
{
	// Code
	uint32_t checkIndex = hashBF(x, key);
	checkIndex = checkIndex % (x->l);
	uint32_t check = valBF(x, checkIndex);
	return check;
	
}

static inline void printBF ( bloomF * x )
{
	// Code
	for(uint32_t i = 0; i < (x->l); i++)
	{
		printf("%u", valBF(x, i));
	}
	printf("\n");
	return;
}

# endif
