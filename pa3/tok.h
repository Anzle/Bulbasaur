/*
* Rob Williams & Sangini Shah
* Section 1
* CS 214 PA3
* tokenizer revamp
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
* Tokenizer type.  You need to fill in the type as part of your implementation.

** This struct acts as the TokenizerStream
** It stores the entire original string into the token variable, and then iterates
** though the stream, keeping track of it's possition with with pos variable
*/
struct TokenizerT_ {
	char *token; //The token stream to read from
	int pos; //
};

typedef struct TokenizerT_ TokenizerT;

/*
* TKCreate creates a new TokenizerT object for a given token stream
* (given as a string).
*
* TKCreate should copy the arguments so that it is not dependent on
* them staying immutable after returning.  (In the future, this may change
* to increase efficiency.)
*
* If the function succeeds, it returns a non-NULL TokenizerT.
* Else it returns NULL.
*
* You need to fill in this function as part of your implementation.
*/
TokenizerT *TKCreate(char * ts);

/*
* TKDestroy destroys a TokenizerT object.  It should free all dynamically
* allocated memory that is part of the object being destroyed.
*
* You need to fill in this function as part of your implementation.
*/
void TKDestroy(TokenizerT * tk);

/*
* TKGetNextToken returns the next token from the token stream as a
* character string.  Space for the returned token should be dynamically
* allocated.  The caller is responsible for freeing the space once it is
* no longer needed.
*
* If the function succeeds, it returns a C string (delimited by '\0')
* containing the token.  Else it returns 0.
*
* You need to fill in this function as part of your implementation.

**THIS Function is supposed to parse the token stream
*/

char *TKGetNextToken(TokenizerT * tk);

