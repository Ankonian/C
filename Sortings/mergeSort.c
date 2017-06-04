# include <stdio.h>
# include <stdint.h>

void merging(uint32_t a[], uint32_t first, uint32_t mid, uint32_t last, uint32_t *moveCount, uint32_t *compare)
{
  //use temporary variables to store starting positions of the two arrays
  uint32_t tempFirst = first;
  uint32_t tempMid = mid + 1;
  uint32_t tempArray[last - first + 1];
  uint32_t tempIndex = 0;
  *compare = 0;
  *moveCount = 0;
  for(uint32_t i = first; i <= last; i += 1)
  {
    //check if first half still has numbers
    if(tempFirst > mid)
    {
      tempArray[tempIndex++] = a[tempMid++];
      *compare += 1;
      *moveCount += 1;
    }
    //check if second half still has numbers
    else if(tempMid > last)
    {
      tempArray[tempIndex++] = a[tempFirst++];
      *compare += 1;
      *moveCount += 1;
    }
    //check if the first half is smaller than the second half
    else if(a[tempFirst] < a[tempMid])
    {
      tempArray[tempIndex++] = a[tempFirst++];
      *compare += 1;
      *moveCount += 1;
    }
    //check if the second half is smaller than the first half
    else
    {
      tempArray[tempIndex++] = a[tempMid++];
      *compare += 1;
      *moveCount += 1;
    }
  }
  for(uint32_t i = 0; i < tempIndex; i += 1)
  {
    a[first++] = tempArray[i];
    *moveCount += 1;
  }
}

void mergeSort(uint32_t a[], uint32_t first, uint32_t last, uint32_t *moveCount, uint32_t *compare)
{
  if(first < last)
  {
    //keep splitting the array in halves
    uint32_t mid = (first + last) / 2;
    mergeSort(a, first, mid, moveCount, compare);
    *moveCount += 1;
    mergeSort(a, mid + 1, last, moveCount, compare);
    *moveCount += 1;
    //merge them back together in order
    merging(a, first, mid, last, moveCount, compare);
  }

}
