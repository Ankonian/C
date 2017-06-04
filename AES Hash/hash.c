# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <stdio.h>
# include "aes.h"
# include "hash.h"
# include "ll.h"

static inline int realLength(int l)
{
	return 16 * (l / 16 +(l % 16 ? 1 : 0));
}

hashTable *newHT(uint32_t length, uint32_t salt[])
{
	hashTable *ht = malloc(sizeof(hashTable));
	ht->l = length;
	for(uint32_t i = 0; i < length; i++)
	{
		ht->h = (listNode **)calloc(ht->l,sizeof(listNode *));
	}
	for(uint32_t i = 0; i < 4; i++)
	{
		ht->s[i] = salt[i];
	}
	return ht;
}

void delHT(hashTable *ht)
{
	delLL(*ht->h);
	free(ht);
	return;
}

listNode *findHT(hashTable *ht, const char *word)
{
	uint32_t index = hash(ht, word) % (ht->l);
	return findLL(&(ht->h[index]), word);

}

void insertHT(hashTable *ht, const char *key, const char *value)
{
	uint32_t index = hash(ht, key) % (ht->l);

	// if(ht->h[index] == NULL)
	// {
	// 	listNode *n = newNode(key, value);
	// 	insertLL(&n, key, value);
	// }
	// else
	// {
	listNode **n = &(ht->h[index]);
	
	insertLL(n, key, value);
	printHT(ht);
	return;
}

uint32_t hash(hashTable *h, const char *key)
{
	uint32_t output[4] = { 0x0 };
	uint32_t sum = 0x0;
	size_t   keyL = strlen(key);
	uint8_t *realKey = (uint8_t *) calloc(realLength(keyL), sizeof(uint8_t));

	memcpy(realKey, key, keyL);

	for (int i = 0; i < realLength(keyL); i += 16)
	{
		AES128_ECB_encrypt((uint8_t *) h->s, (uint8_t *) realKey + i, (uint8_t *) output);
		sum ^= output[0] ^ output[1] ^ output[2] ^ output[3];
	}
	free(realKey);
	return sum;
}
void printHT(const hashTable *ht)
{
	for(uint32_t i = 0; i < (ht->l); i++)
	{
		if(ht->h[i] != NIL)
		{
			printf("h[%u]: ", i);
			printLL(ht->h[i]);
		}
	}
	printf("\n");
	return;
}
