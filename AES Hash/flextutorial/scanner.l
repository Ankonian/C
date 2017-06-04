/* 
 *  scanner.l
 *	A file defining a scanner in lex
 *	An input file for flex consists of three sections, separated by %%
 *
 *	definitions
 *	%%
 *	rules
 *	%%
 *	code
 *
 *	Author: Boris Gorshenev <bgorshen@ucsc.edu>
*/


%top{
 /* By default, the definitions and rules sections do not contain
  * C code. It must be enclosed in %{ %} or %top{ }.
  * This code block includes a header and defines some variables;
  * since we want this to occur at the beginning of the file, it
  * is enclosed by a top block.  
 */
 # include "flextutorial.h" 
 // This header contains an enum which this tutorial uses to
 // make the values returned by the scanner more readable
 int line_count = 0;	// We'd like to count the number of lines
 int word_count = 0;	// We'd like to count the number of words
 int flex_count = 0;
	// For fun: let's count occurances of the word "flex"
}



/* The definitions section contains pairs of names and
 * definitions, which simplify the rules in the next section
 */

SIGN [+-]
/* This defines SIGN to represent [+-]
 * A group of characters enclosed by [] forms a character class,
 * which matches any character within that class. So, a SIGN is
 * a plus or a minus
 */

DIGIT [0-9]
/* This defines DIGIT to be a character class consisting of the
 * decimal digits. The '-' between two characters causes it to
 * be interpreted as the range of characters between the first
 * and second characters. In the SIGN definition above, '-' just
 * matches a '-', since there is no character following it.*/

LETTER [A-Za-z]
/* This defines LETTER to be any upper or lower case letter.*/

WHITESPACE [ \t]
/* WHITESPACE matches spaces and tabs.*/

NEWLINE [\r\n]
/* NEWLINE matches newlines and carriage returns */

PUNCTUATION [~‘!@#$%^&*()_+\-={}|\\\[\]:;\"\’<>,\./?]
/* All the punctuation you could ever dream of. Note the
 * backslashes '\' being used to escape [, -, ], \, ", and '
 * These characters have special meanings flex, and thus cannot
 * represent themselves without being escaped. */


%%

 /* The rules section consists of pairs of the form 
  * pattern action
  * where "pattern" is a regular expression and "action" is a
  * C statement.
  * Note that all comment blocks are slightly indented here:
  * flex expects anything at the beginning of a line to be a
  * regular expression.
  */

flex					{ flex_count++; word_count++; return TOKEN_WORD; }
 /* Upon encountering the literal word "flex", increment counters and
  * return that we have found a word.
  */

((J|j)(A|a)(V|v)(A|a))	{ }
 /* We don't like Java. So, whenever we encounter the word "java" we do 
  * nothing. The OR operator '|' matches the characters on
  * either side of it. So, (J|j) will match both lower and upper
  * case 'J'.
  * There's a nicer way to do case-insensitivity, but this rule
  * is being used to demonstrate OR.
  */

({LETTER})+				{ word_count++; return TOKEN_WORD; } 
 /* A name enclosed in {} substitutes its definition into a
  * rule. The '+' operator matches ONE or MORE of the preceding
  * symbol.
  * Here, we consider any sequence of letters to be a
  * word.
  * That's a small lie. "flex" is considered a word, but is not
  * matched here. "java" is doubleplusbadlang, and should be
  * removed from the language.
  */
{SIGN}?{DIGIT}+ 		{ return TOKEN_NUMBER; }
 /* The '?' operator matches ZERO or ONE occurences of the
  * preceding symbol.
  * This scanner will consider a string of decimal digits,
  * possibly preceded by a + or -, to be a number. 
  */
 
{PUNCTUATION}			{ return TOKEN_PUNCTUATION; }

{NEWLINE}				{ line_count++; }
 /*
  * We want to count lines in this tutorial, but the newlines
  * themselves have no value to us, so we return nothing.
  */

{WHITESPACE}+			{ }
 /*
  * Like newlines, whitespace does not make up tokens which are
  * of interest to us. We do, however, want to recognize it.
  */

<<EOF>> 				{return TOKEN_EOF;}
 /*
  * <<EOF>> is matched when the scanner reaches the end of the
  * file it is reading.
  */

"//"[^\n]*\n			{ }
 /*
  * This pattern is a bit more complicated. "//" matches a pair
  * of slashes. The '^' in "[^\n]" NEGATES the character class,
  * causing it to match any character not in the brackets.
  * The '*' operator matches ZERO or MORE instances of the
  * preceding symbol.
  * This pattern matches any inline C-style comments,
  * without returning any value or printing anything. 
  * A newline is matched at the end to ensure the line count is
  * not incremented (may cause problems with carriage return).
  */

. 						{return TOKEN_INVALID;}
 /*
  * The '.' operator matches any character EXCEPT a newline
  * (equivalent to [^\n]).
  * Here it is used alone to allow the scanner to return when it
  * encounters something it cannot identify.
  */

%%

/*
 * The user code section contains C code. A flex input file is not
 * required to contain a code section; this tutorial has a few
 * functions for demonstrative puposes.
 */

int lineCount(void)
{
	return line_count;
}
int flexCount(void)
{
	return flex_count;
}
int wordCount(void)
{
	return word_count;
}
