# include <stdio.h>
# include <stdint.h>

# ifdef _INSTRUMENTED
# define SWAP(x, y) { uint32_t t = x; x = y; y = t; ; moveCount += 3; }
# else
# define SWAP(x, y) { uint32_t t = x; x = y; y = t; ; }
# endif

uint32_t compareMin = 0;
uint32_t minIndex(uint32_t a[], uint32_t first, uint32_t last)
{
	uint32_t smallest = first;
	for(uint32_t i = first; i < last; i += 1)
	{
		smallest = a[i]<a[smallest] ? i : smallest;
		compareMin += 1;
	}
	return smallest;
}

void minSort(uint32_t a[], uint32_t length)
{
	printf("%d elements ", length);
	printf("\n");
	uint32_t moveCount = 0;

	for(uint32_t i = 0; i < length - 1; i += 1)
	{
		uint32_t smallest = minIndex(a, i, length);
		if(smallest != i)
		{
			SWAP(a[smallest], a[i]);
			moveCount += 3;
	//		compare += 1;
		}
		else
		{
	//		compare += 1;
		}
	}
	printf("%d moves ", moveCount);
	printf("\n");
	printf("%d compares", compareMin);
	printf("\n");
	return;
}
