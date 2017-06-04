# include <stdio.h>
# include <stdint.h>
# include <inttypes.h>
# include <stdlib.h>
# include <getopt.h>
# include "minSort.h"
# include "bubbleSort.h"
# include "insertionSort.h"
# include "quickSort.h"
# include "mergeSort.h"
# include "bv.h"

enum sortings {min, bubble, insert, quick, merge};

int main(int argc, char **argv)
{
/*
	uint32_t length = 7;
	uint32_t a[] = {653, 2, 34, 9, 77, 89, 655};
	quickSort(a, 7);
	for(uint32_t i = 0; i < length; i += 1)
	{
		printf("%"PRIu32" ", a[i]);
	}
	printf("\n");
*/
	uint32_t arraySize = 100;
	uint32_t seed = 8062022;
	uint32_t printSize = 100;
	uint32_t moveCount = 0;
	uint32_t compare = 0;
	bitV * bv = newVec(5);
	int selections;
	while ((selections = getopt(argc, argv, " AmbiqMp:r:n:")) != -1)
	{
		switch (selections)
		{
			case 'r':
			{
				//get the random sseed
				seed = atoi(optarg);
				break;
			}
			case 'n':
			{
				//get the range of numbers
				arraySize = atoi(optarg);
				break;
			}
			case 'p':
			{
				//get the number of numbers to be printed
				printSize = atoi(optarg);
				break;
			}
			case 'A':
			{
				//use all
				oneVec(bv);
				printf("All Sort\n");
				break;
			}
			case 'm':
			{
				//use minSort
				setBit(bv, 0);
				printf("minSort\n");
				break;
			}
			case 'b':
			{
				//use bubbleSort
				setBit(bv, 1);
				printf("bubbleSort\n");
				break;
			}
			case 'i':
			{
				//use insertionSort
				setBit(bv, 2);
				printf("insertionSort\n");
				break;
			}
			case 'q':
			{
				//use quickSort
				setBit(bv, 3);
				printf("quickSort\n");
				break;
			}
			case 'M':
			{
				//use mergeSort
				setBit(bv, 4);
				printf("mergeSort\n");
				break;
			}
		}
	}
	//set size of the array of numbers
	printf("printSize: %d\n", printSize);
	printf("arraySize: %d\n", arraySize);
	printf("seed: %d\n", seed);
	uint32_t *arrayNum = calloc(arraySize, sizeof(uint32_t));
	srand(seed);
	for(uint32_t i = 0; i < arraySize; i += 1)
	{
		arrayNum[i] = rand() % 16777215;
//		printf("%d ", i);
	}
	for(uint32_t i = 0; i < lenVec(bv); i += 1)
	{
		printf("%d ", valBit(bv, i));
	}
	printf("\n");
	//use the appropriate sorting to sort the array
	for(uint32_t i = 0; i < lenVec(bv); i += 1)
	{
			if(valBit(bv, i))
			{
				switch(i)
				{
					case 0:
					{
						printf("minSort\n");
						srand(seed);
						for(uint32_t i = 0; i < arraySize; i += 1)
						{
							arrayNum[i] = rand() % 16777215;
						}
						minSort(arrayNum, arraySize);
						for(uint32_t i = 0; i < printSize && i < arraySize; i += 1)
						{
							printf("%9d ", arrayNum[i]);
						}
						printf("\n");
						break;
					}
					case 1:
					{
						printf("bubbleSort\n");
						srand(seed);
						for(uint32_t i = 0; i < arraySize; i += 1)
						{
							arrayNum[i] = rand() % 16777215;
						}
						bubbleSort(arrayNum, arraySize, &moveCount, &compare);
						for(uint32_t i = 0; i < printSize && i < arraySize; i += 1)
						{
							printf("%9d ", arrayNum[i]);
						}
						printf("\n");
						break;
					}
					case 2:
					{
						printf("insertionSort\n");
						srand(seed);
						for(uint32_t i = 0; i < arraySize; i += 1)
						{
							arrayNum[i] = rand() % 16777215;
						}
						insertionSort(arrayNum, arraySize);
						for(uint32_t i = 0; i < printSize && i < arraySize; i += 1)
						{
							printf("%9d ", arrayNum[i]);
						}
						printf("\n");
						break;
					}
					case 3:
					{
						printf("quickSort\n");
						srand(seed);
						for(uint32_t i = 0; i < arraySize; i += 1)
						{
							arrayNum[i] = rand() % 16777215;
						}
						moveCount = 0;
						compare = 0;
						quickSort(arrayNum, 0, arraySize - 1, &moveCount, &compare);
						printf("%d moves\n", moveCount);
						printf("%d compares\n", compare);
						for(uint32_t i = 0; i < printSize && i < arraySize; i += 1)
						{
							printf("%9d ", arrayNum[i]);
						}
						printf("\n");
						break;
					}
					case 4:
					{
						printf("merge Sort\n");
						srand(seed);
						for(uint32_t i = 0; i < arraySize; i += 1)
						{
							arrayNum[i] = rand() % 16777215;
						}
						mergeSort(arrayNum, 0, arraySize - 1, &moveCount, &compare);
						printf("%d moves\n", moveCount);
						printf("%d compares\n", compare);
						for(uint32_t i = 0; i < printSize && i < arraySize; i += 1)
						{
							printf("%9d ", arrayNum[i]);
						}
							printf("\n");
						break;
					}
				}
			}
	}
	free(arrayNum);
	free(bv);
	return 0;
}
