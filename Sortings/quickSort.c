# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>

# ifdef _INSTRUMENTED
# define SWAP(x, y) { uint32_t t = x; x = y; y = t; moveCount += 3 }
# else
# define SWAP(x, y) { uint32_t t = x; x = y; y = t; ; }
# endif

uint32_t partition(uint32_t a[], uint32_t first, uint32_t last, uint32_t *moveCount, uint32_t *compare)
{
    uint32_t pivot = a[last - 1];
    uint32_t i = (first - 1);
    for (uint32_t j = first; j < last; j++)
    {
        *compare += 1;
        if (a[j] <= pivot)
        {
            i += 1;
            SWAP(a[i], a[j]);
            *moveCount += 3;
        }
    }
    SWAP(a[i + 1], a[last]);
    return (i + 1);
}
void quickSort(uint32_t a[], uint32_t first, uint32_t last, uint32_t *moveCount, uint32_t *compare)
{
    if(first < last)
    {
      uint32_t pivotPosition = partition(a, first, last, moveCount, compare);
      quickSort(a, first, pivotPosition - 1, moveCount, compare);
      quickSort(a, pivotPosition + 1, last, moveCount, compare);
    }
}
