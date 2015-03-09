/*
* Rob Williams & Sangini Shah
* Section 1
* CS 214 PA3
* tokenizer revamp
*/



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

TokenizerT *TKCreate(char * ts) {
	if (ts == 0){
		return NULL;
	}
	else {
		//Should probably check these for existence
		TokenizerT *tokenizer = (TokenizerT *)calloc(1, sizeof(TokenizerT));
		tokenizer->token = (char*)malloc(sizeof(char*)*(strlen(ts) + 1));


		strcpy(tokenizer->token, ts); //Copy the TokenStream
		tokenizer->pos = 0; //the position in the TokenStream
		return tokenizer;
	}
}

/*
* TKDestroy destroys a TokenizerT object.  It should free all dynamically
* allocated memory that is part of the object being destroyed.
*
* You need to fill in this function as part of your implementation.
*/

void TKDestroy(TokenizerT * tk) {
	free(tk->token);
	free(tk);
}

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


char *TKGetNextToken(TokenizerT * tk){

if (tk == NULL || tk->pos == strlen(tk->token))
		return NULL;

	int length = 0;
	int start = tk->pos;
	char* word = NULL;

	/*Begin parsing*/
	/*Word*/
	if (isalpha(tk->token[tk->pos])){
		length++;
		while (isalnum(tk->token[++tk->pos]))
			length++;
		/*ret = (char*)malloc(sizeof(char*)*(length + 8)); //add 1 for NULL and 7 for "Word_\"\""
		strcpy(ret, "Word \"");
		strncat(ret, tk->token + start, length);
		strcat(ret, "\"\0");*/
		word = (char*)malloc(sizeof(char*)*(length+1));
		strncpy(word, tk->token + start, length);
		word[length] = '\0';
		
	}
	else{
	return TKGetNextToken(++tk->pos);
	}
	return word;
}