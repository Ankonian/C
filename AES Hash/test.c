#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes.h"



int main()
{
  char* key = "asde";
  char* test= "this is a test string";
  char* test1 ;
  char out[4] = {0x0};
  char out2[4] = {0x0};
  uint32_t s[4];
  s[0] = 1;
  s[1] = 2;
  s[2]=3;
  s[3]=4;
/*  //printf("no e\n");
  AES128_ECB_encrypt((uint8_t *)s,  (uint8_t*)key,  (uint8_t *)out);
  AES128_ECB_decrypt((uint8_t*)s,  (uint8_t*) out, (uint8_t*)out2);
  printf("input: %s output %s\n", key, out2);
  return 0;*/
   uint32_t output [4] = { 0x0 };
    uint32_t sum = 0x0;
     int keyL = strlen (key);
      uint8_t * realKey = ( uint8_t *) calloc ( ( keyL ), sizeof (
            uint8_t ));

       memcpy ( realKey , key , keyL );

        for ( int i = 0; i <  ( keyL ); i += 16)
           {
              AES128_ECB_encrypt (( uint8_t *) s, // Salt
                   ( uint8_t *) realKey + i, // Input
                    ( uint8_t *) output ); // Output
               sum ^= output [0] ^ output [1] ^ output [2] ^ output [3];
                }

         free ( realKey );
         printf("hashf:%u\n", sum%64);
}

/*
static inline bloomF * newBF ( uint32_t l, uint32_t b[])
{
  bloomF bf = malloc(sizeof(bloomF));
  bf->l  =l;
  //bf->v = (void *) NULL;
  bf->s=b;
}

static inline bloomF * newBF ( uint32_t l, uint32_t b[])
{
  delete(v);
  bloomF->v = NULL;
  free(bloomF->l);
  bloomF->l= NULL;
  for(int i =0;i<4;){
bloomF->s[i]=NULL;
    }
  bloomF->s=NULL;
  free(bloomF);
  bloomF = NULL;

}
*/


