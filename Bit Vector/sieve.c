/*
 *sieve.c
 *Author: Darrell Long
*/
#include <math.h>
#include "bv.h"

void sieve(bitV *v)
{
	oneVec(v) ;	// Assume all numbers are prime
	clrBit(v, 0);	// 0 is just 0
	clrBit(v, 1);	// 1 is unity
	setBit(v, 2);	// 2 is the smallest prime
	for(uint32_t i = 2; i <= sqrtl(lenVec(v)); i += 1)
	{
		if(valBit(v, i)) //If the number is prime
		{
			for(uint32_t k = 0; (k + i) * i <= lenVec(v); k += 1)
			{
				clrBit(v, (k + i) * i); //Its multiples are composite
			}
		}
	}
	return;
}
