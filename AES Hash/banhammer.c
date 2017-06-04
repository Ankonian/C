# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include "bf.h"
# include "aes.h"
# include "hash.h"
# include "ll.h"
# include "flex.h"

bool moveToFront = false;
/*
int yylex(void);
extern char* yytext;
extern FILE* yyin;
*/
int main(void)
{
	uint32_t initA[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a}; // First Bloom filter
	uint32_t initB[] = {0xDeadBeef, 0xFadedB0a, 0xCafeD00d, 0xC0c0aB0a}; // Second Bloom filter
	uint32_t initH[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0Babe}; // Hash table

	uint32_t bfSize = 1048576;
	uint32_t htSize = 10000;

	bloomF * bloomf1 = newBF(bfSize, initA);
	bloomF * bloomf2 = newBF(bfSize, initB);
	hashTable * ht = newHT(htSize, initH);

	FILE * badspeakf = fopen("badspeak.txt", "r");
	FILE * newspeakf = fopen("newspeak.txt", "r");

	char badspeakWord[128];
	char oldspeakWord[128];
	char newspeakWord[128];

	if(badspeakf)
	{
		while(fscanf(badspeakf, " %s\n", badspeakWord) != EOF)
		{
			fscanf(badspeakf, " %s\n", badspeakWord);
			setBF(bloomf1, badspeakWord);
			setBF(bloomf2, badspeakWord);
			insertHT(ht, badspeakWord, NULL);
		//	printBF(bloomf1);
			printHT(ht);
		}
	}
	if(newspeakf)
	{
		while(fscanf(newspeakf, "%s %s\n", oldspeakWord, newspeakWord) != EOF)
		{
			setBF(bloomf1, oldspeakWord);
			setBF(bloomf2, oldspeakWord);
			insertHT(ht, oldspeakWord, newspeakWord);
			//printHT(ht); //error right now is that it prints empty spaces
		}
	}
	fclose(badspeakf);
	fclose(newspeakf);
	
	
//	char word[128];

	delBF(bloomf1);
	delBF(bloomf2);
	delHT(ht);
	return 0;


}
