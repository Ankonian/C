//The section of the code where it finds the factors of composite are given by Darrell Long
#include <stdio.h>
#include <stdbool.h>
#include "sieve.h"
#include "bv.h"

int main(void)
{
	uint32_t factors[1000];
	uint32_t length = 100000;
	bitV *vec = newVec(length);
	oneVec(vec);
	sieve(vec);
	//look through the bit vector
	for(uint32_t i = 2; i <= lenVec(vec); i++)
	{
		//print out the prime numbers
		if(valBit(vec, i) == 1)
		{
			printf("%d P\n", i);
		}
		//print out the composite numbers
		else
		{
			printf("%d C: ", i);
			uint32_t p = 2;
			uint32_t n = i;
			//CODE PROVIDED BY DARRELL LONG
			while(n > 1)
			{
				if(n % p == 0)
				{
					n /= p;
					printf(" %d", p);
				}
				else
				{p += 1;}
		}
		//get all the factors and the sum of the factors of the composite number
		uint32_t factorSum = 0;
		uint32_t incrementor = 0;
		for(uint32_t factor = 1; factor < i; factor++){
			if(i % factor == 0){
				factors[incrementor] = factor;
				incrementor++;
				factorSum+=factor;
			}
		}
		//if the sum matches the number, the number is perfect number
		if(factorSum == i)
		{
			printf("\n%d E:", i);
			for(uint32_t j = 0; j < incrementor; j++)
			{
				printf(" %d", factors[j]);
			}
		}
		printf("\n");
	}
}
return 0;
}
