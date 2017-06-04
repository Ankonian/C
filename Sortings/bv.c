#include "bv.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bitV* newVec(uint32_t num)
{
  bitV* vec = calloc(1, sizeof(bitV));
  vec->l = num;
  vec->v = (uint8_t * ) (calloc(1, ceil(num/8)));
  return vec;
}
void delVec(bitV * vec)
{
  free(vec->v);
}
void oneVec(bitV * vec)
{
  //use bitwise and to make newVec all 1s
  for(unsigned x = 0;x<ceil(vec->l/8)+1;x++){
    *(vec->v+x) = *(vec->v+x) | ~*(vec->v+x);
  }
}
void setBit(bitV * vec, uint32_t num)
{
  //use bitwise or to make one bit of newVec 1
  (*(vec->v+(num/8))) |= (1<<(7-num%8));
}
void clrBit(bitV * vec, uint32_t num)
{
  //use bitwise and to make one bit of newVec 0
   (*(vec->v+(num/8))) &= ~(1<<(7-num%8));
}
uint8_t valBit(bitV * vec, uint32_t num)
{
  //get the value of the bit at uint32_t
  uint8_t value = (*(vec->v+(num/8)))>>(7-(num%8)) & 1;
  return value;
}
uint32_t lenVec(bitV * vec)
{
  //get the length of newVec
  return vec->l;
}
