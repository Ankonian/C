# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>

# ifdef _INSTRUMENTED
# define SWAP(x, y) { uint32_t t = x; x = y; y = t; moveCount += 3 }
# else
# define SWAP(x, y) { uint32_t t = x; x = y; y = t; ; }
# endif


void bubbleSort(uint32_t a[], uint32_t length, uint32_t *moveCount, uint32_t *compare)
{
	(*compare) = 0;
	(*moveCount) = 0;
	bool swapped = true;
	//for(uint32_t i = 1; i < length; i += 1)
	while(swapped)
  	{
			swapped = false;
    		for(uint32_t j = 0; j < length - 1; j += 1)
    		{
      			if(a[j+1] < a[j])
      			{
        			 SWAP(a[j], a[j+1]);
							// uint32_t temp = a[j];
							// a[j]=a[j+1];
							// a[j+1]=temp;
							(*compare) += 1;
							(*moveCount) += 3;
							swapped = true;
      			}
						(*compare) += 1;
    		}
  	}
		printf("%d elements\n", length);
		printf("%d moves\n", *moveCount);
		printf("%d compares\n", *compare);
}
