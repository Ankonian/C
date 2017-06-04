# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "aes.h"
# include "bf.h"

// Each function has its own hash function, determined by the salt.
static int realLength(int l)
{
	return 16 * (l / 16 +(l % 16 ? 1 : 0));
}

uint32_t hashBF(bloomF *bf, const char *word)
{
	uint32_t index = 0;
	uint32_t output [4] = { 0x0 };
	int keyL = strlen (word);
	uint8_t * realKey = ( uint8_t *) calloc ( ( keyL ), sizeof (uint8_t ));

	memcpy ( realKey , word , keyL );

	for ( int i = 0; i <  realLength( keyL ); i += 16)
	{
		AES128_ECB_encrypt (( uint8_t *) bf->s, // Salt
		( uint8_t *) realKey + i, // Input
		( uint8_t *) output ); // Output
		index ^= output [0] ^ output [1] ^ output [2] ^ output [3];
	}
	free ( realKey );
	return index;
}
