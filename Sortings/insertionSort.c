# include <stdio.h>
# include <stdint.h>

# ifdef _INSTRUMENTED
# define SWAP(x, y) { uint32_t t = x; x = y; y = t; moveCount += 3 }
# else
# define SWAP(x, y) { uint32_t t = x; x = y; y = t; ; }
# endif

void insertionSort(uint32_t a[], uint32_t length)
{
  //print out the number of elements
  printf("%d elements ", length);
  printf("\n");

  uint32_t compare = 0;
  uint32_t moveCount = 0;
  uint32_t temp;
  int j = 0;
  for(uint32_t i = 1; i < length; i += 1)
  {
    temp = a[i];
    moveCount += 1;
    j = i - 1;
    while(j >= 0 && a[j] > temp)
    {
      compare += 1;
      a[j+1] = a[j];
      moveCount += 1;
      j = j-1;
    }
    a[j+1] = temp;
  }
  //print out the counts for moves and compares
  printf("%d moves ", moveCount);
  printf("\n");
  printf("%d compares", compare);
  printf("\n");
}
