/*  flextutorial.c
    This file is used to test the scanner defined in scanner.l 
    Author: Boris Gorshenev <bgorshen@ucsc.edu>
*/

# include <stdio.h>
# include <errno.h>
# include "flextutorial.h"


/*
 * Running flex on scanner.l will create a C file called
 * lex.yy.c
 * flextutorial.c uses some of the functions and variables in
 * lex.yy.c to interact with the scanner.
 *
 * Normally, these would be declared in a header, but for the
 * sake of readability they are declared here instead.
 */



int yylex(void);	
/* 
 * yylex() runs scanner until it gets a token, and returns the
 * value returned by the action associated with that token.
 */

extern char* yytext;
/*
 * When yylex() returns, the text matched by the scanner is
 * stored in a string accessible through the pointer yytext.
 */


extern FILE* yyin;
/*
 * yyin is the file from which the scanner will get its input.
 * By default, it is stdin.
 */

int lineCount(void);
int wordCount(void);
int flexCount(void);
// These functions were defined in the code section of scanner.l



void getTokens(void)
/*
 * The main loop of this program.
 * It repeatedly calls yylex() and prints information about the output
 */
{
	int tokenID = 0;
	while (tokenID != TOKEN_EOF)
	// Loop until the end of the file.
	{
		tokenID = yylex(); 
		// Get a token from the scanner.
	
		switch (tokenID)
		{
			case TOKEN_WORD:
				// In the case of a word, print it out.		
				printf("Word                - %s\n",yytext);
				break;
			case TOKEN_NUMBER:
				// In the case of a number, also print it out.
				// atoi() could be used to convert this string
				// representation of a number to an integer.		
				printf("Number              - %s\n",yytext);
				break;
			case TOKEN_PUNCTUATION:
				printf("Punctuation mark    - %s\n",yytext);
				break;
			case TOKEN_EOF:
				// Upon reaching the end of the file, print the
				// information we've collected about it.
				printf("END OF FILE\n");
				printf("%d lines\n",lineCount());
				printf("%d words\n",wordCount());
				printf("%d instances of the word 'flex'\n",flexCount());
				break;
			default:
				// Notify the user of any tokens the scanner
				// does not recognize.
				printf("Unknown token       - %s\n",yytext);
				break;
		}
	}

	return; // Upon reaching the end of the file, stop.
}


int main(int argc, char** argv) 
/*
 *	Set the file from which the scanner will read.
 *	It will return a 0 on success, or an error code if it fails to open a file.
 */
{
	if (argc == 1)
	// If there are no arguments, read from standard input
	{
		yyin = stdin;
		getTokens(); // Enter the main loop of the program
		return 0;
	}
	else
	{
		yyin = fopen(argv[1],"r");
		// Try to open the file named by the first command line argument
		if (yyin == NULL)
		// If the file fails to open, print an error message.
		// Otherwise, read from the file
		{
			perror("flextutorial");
			return errno;
		}
		else 
		{

			getTokens(); // Enter the main loop of the program
			fclose(yyin);
			return 0;
		}
	}
}
