// bv.h — Bit Vector interface
// Author: Prof. Darrell Long

# ifndef _BVector
# define _BVector
# include <stdint.h>

typedef struct bitV {
	uint8_t *v;
	uint32_t l;
} bitV;

bitV *newVec(uint32_t num);

void delVec(bitV * vec);

void oneVec(bitV * vec);

void setBit(bitV * vec, uint32_t num);

void clrBit(bitV * vec, uint32_t num);

uint8_t valBit(bitV * vec, uint32_t num);

uint32_t lenVec(bitV * vec);
# endif
