#ifndef _SIEVE
#define _SIEVE

#include "bv.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// set the bit at k to k.
// retrieve vector[k/8]. 
// retrive the bit number by shifting 01 by the number. 
// ex: k = 9, vector = [11001101][00000000]
// 9 & 07: 10001 & 00111 = 00001 
// 1 << 1 = 0b10 
// then, OR the bit with the vector to ensure that the bit is set to 1, and the others remain
// the same.
// 11001101 |= 00000010 = 11001111; 
#define SETBIT(vector, k) vector[k >> 3] |= (01 << (k & 07))

//
//CLRBIT works the same as setBit, only reversed.
// take logical not for all the bits so that it's inversed.
// and it so that only the bit in question is set to 0, and the others remain the same.
#define CLRBIT(vector, k) vector[k >> 3] &= ~(01 << (k & 07))

//
// k is the bit number you want to set.
// vector is the bitvector that you have.
// 07 = 7 in octal = 111
#define GETBIT(vector,k) (vector[k >> 3] & 01 << (k & 07) ) >> (k & 07) 
// example: k = 9, vector = [11001101][00000000]:
// vector[9/8] = vector[1]
// vector[1] = 11001101
// & comes after <<.
// 01 << 9 & 07
bitV *newVec(uint64_t x) {
    bitV *dirtyBit = malloc(sizeof(bitV)); // reserve the amount of bytes needed for one bitV.
    // reserve the amount of bytes needed for x uint8_t's. 
    // each uint8_t's will hold 8 prime truth values, each corresponding to its prime.
    // e.g. vector[0] will hold the truth values of numbers 0 - 7.
    if(dirtyBit)
    {
	dirtyBit->vector = (uint8_t * ) calloc(x / 8 + 1, sizeof(uint8_t)); // dirtyBit->vector = (*dirtyBit).vector
    // (x * ) calloc(y, z) resereves y spaces of size z of type x. 
        if(dirtyBit->vector)
	{
		dirtyBit->length = x; // add the length of the vector too, for lenVec().
        	return dirtyBit; // return a pointer to the bitvector.
	}
    	else
	{
		printf("CALLOC FAILED.\n");
		return (void *) 0; // return a pointer to the bitvector.
    	}
    }
    else
    {
	printf("MALLOC FAILED.\n");
    	return (void *) 0;
    }
}
            
void delVec(bitV *dirtyBit)
{
    // when I reserve memory in the space, I need to free it. 
    // If I don't free the memory, it will be stuck in the UNIX RAM forever (unless we have a special program 
    // that can detect unused memory and free it)
    // so, to do that, we call free.
    // we need to free both the memory space reserved for our vector, and the memory space used for our bitV
    // structure. to do that, use the free() function. free() takes in a pointer. It take
    free(dirtyBit->vector);
    free(dirtyBit); // gotta free everything you reserved memory for. In C, you must collect your garbage.
    return;
}
               
void oneVec(bitV *dirtyBit)
{
    // memset sets every part from the beginning of dirtyBit->vector to dirtyBit->length to 255.
    // include string.h for it to work. 
    // 2^8 - 1 = 255 = 0b11111111
    memset(dirtyBit->vector, 255, dirtyBit->length); 
    return;
}

void setBit(bitV *dirtyBit, uint64_t x)
{
	/*
	if(x > lenVec(dirtyBit))
	{
		printf("TRYING TO SET BIT OUTSIDE OF RANGE.\n");
	}
	*/
    //sets a bit at point of impact.
	if(x > lenVec(dirtyBit))
	{
		dirtyBit->length *= 2;
		dirtyBit->vector = realloc(dirtyBit->vector, (dirtyBit->length / 8 + 1) * sizeof(uint8_t));
	}
	SETBIT(dirtyBit->vector, x);
	return;
}

void clrBit(bitV *dirtyBit, uint64_t x)
{
    //see above. It clears a bit at position x.
	
	if(x > lenVec(dirtyBit))
	{
		dirtyBit->length *= 2;
		dirtyBit->vector = realloc(dirtyBit->vector, (dirtyBit->length / 8 + 1) * sizeof(uint8_t));
	}
	CLRBIT(dirtyBit->vector, x);
	return;
}

uint8_t valBit(bitV *dirtyBit, uint64_t x)
{
	// see above.
	return GETBIT(dirtyBit->vector, x); 
}

uint64_t lenVec(bitV *dirtyBit)
{ 
    // make a dummy variable, set it to dirtyBit->length. 
    // for some reason, the compiler yells at me when I use return dirtyBit->length.
    // I have this function because it's considered bad form to call a struct's member outside of the
    // bitvector's function. 
    // So, the creator of the bitvector struct must provide a function that returns 
    uint64_t l = dirtyBit->length;
    return l;
}

#endif


