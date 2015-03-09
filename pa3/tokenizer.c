/*
* Rob Williams and Sangini Shah
* Section 1
* CS214 PA1
* tokenizer.c
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

char *TKGetNextToken(TokenizerT * tk) {

	if (tk == NULL || tk->pos == strlen(tk->token))
		return NULL;

	int length = 0;
	int start = tk->pos;
	char* ret = NULL;
	char flag = '0';
	
	char unkn;
	int hex;
	char hchar[3];

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
		char * word = (char*)malloc(sizeof(char*)*(length+1));
		strncpy(word, tk->token + start, length);
		word[length] = '\0';
		if (strcmp(word, "if") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "auto") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "break") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "case") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "char") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "const") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "continue") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "default") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "do") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "double") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "else") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "enum") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "extern") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "float") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "for") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "goto") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "int") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "long") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "register") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "return") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "short") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "signed") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "sizeof") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "static") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "struct") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "switch") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "typedef") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "union") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "unsigned") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "void") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "volatile") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else if (strcmp(word, "while") == 0) {
			ret = (char*)malloc(sizeof(char*)*(length + 11)); //add 1 for NULL and 7 for "Keyword_\"\""
			strcpy(ret, "Keyword \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
			free(word);
		}
		else {
			ret = (char*)malloc(sizeof(char*)*(length + 8)); //add 1 for NULL and 7 for "Word_\"\""
			strcpy(ret, "Word \"");
			strcat(ret, word);
			strcat(ret, "\"\0");
		}
	}
	/*Number*/
	else if (isdigit(tk->token[tk->pos])){
		length++;
		/*Begin oct/hex check*/
		if (tk->token[tk->pos] == 0x30){
			tk->pos++;

			if/*Hex*/ (tk->token[tk->pos] == 0x58 || tk->token[tk->pos] == 0x78){
				length++;
				while (isxdigit(tk->token[++tk->pos]))
					length++;
				ret = (char*)malloc(sizeof(char*)*(length + 7)); //add 1 for NULL and 6 for "Hex_\"\""
				strcpy(ret, "Hex \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
			}

			else/*OCT*/{
				while (isdigit(tk->token[tk->pos])){
					length++;
					tk->pos++;
				}
				ret = (char*)malloc(sizeof(char*)*(length + 7)); //add 1 for NULL and 6 for "Oct_\"\""
				strcpy(ret, "Oct \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
			}
		}//End Hex/Oct Check
		else /*Int and Float*/{

			while (isdigit(tk->token[++tk->pos]))
				length++;
			if (tk->token[tk->pos] == 0x2e){ /*Is there a decimal*/
				length++;
				while (isdigit(tk->token[++tk->pos])) /*Keep getting digits*/
					length++;
				flag = 'f'; //set to f for float
			}
			if (tk->token[tk->pos] == 0x45 || tk->token[tk->pos] == 0x65){
				length++;
				tk->pos++;
				if (tk->token[tk->pos] == 0x2d) /*There can only be a - after the e/E*/
					length++;
				while (isdigit(tk->token[++tk->pos])) /*Keep getting digits*/
					length++;
				flag = 'f';
			}

			if (flag == 'f'){
				ret = (char*)malloc(sizeof(char*)*(length + 9)); //add 1 for NULL and 8 for "Float_\"\""
				strcpy(ret, "Float \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
			}
			else{
				ret = (char*)malloc(sizeof(char*)*(length + 7)); //add 1 for NULL and 6 for "Int_\"\""
				strcpy(ret, "Int \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
			}

		}//End int/float check
	}
	else{
		switch (tk->token[tk->pos]){
		case 0x20: //space
		case 0x09: //tab
		case 0x0a: //newline
		case 0x0d: //carriageReturn
			tk->pos++;
			ret = TKGetNextToken(tk); //continue through the stream
			break;
		case '/':
			tk->pos++;
			if (tk->token[tk->pos] == '*'){
				while ((tk->token[tk->pos + 1] != '*' && tk->token[tk->pos + 2] != '/') && tk->token[tk->pos] != '\0')
				{/*loop*/tk->pos++;
				}
				tk->pos = tk->pos + 3;
				ret = TKGetNextToken(tk); //continue through the stream
				break;
			}
			else if (tk->token[tk->pos] == '/'){
				/*Loop till end of line*/
				while ((tk->token[tk->pos + 1] != 0x0a) && tk->token[tk->pos] != '\0')
				{
					tk->pos++;
				}
				tk->pos = tk->pos + 2;
				ret = TKGetNextToken(tk); //continue through the stream
				break;
			}
			else{
				//Operators that start with /
				length++;
				if (tk->token[tk->pos] == '='){
					/* /= */
					length++;
					ret = (char*)malloc(sizeof(char*)*(length + 16));
					strcpy(ret, "Divideequals \"");
					strncat(ret, tk->token + start, length);
					strcat(ret, "\"\0");
					tk->pos = tk->pos + 1;
					break;
				}
				else {
					/* / */
					ret = (char*)malloc(sizeof(char*)*(length + 10));
					strcpy(ret, "Divide \"");
					strncat(ret, tk->token + start, length);
					strcat(ret, "\"\0");
					break;
				}
			}
		case '"':
			length++;
			while ((tk->token[tk->pos + 1] != '"') && tk->token[tk->pos] != '\0'){
				length++;
				tk->pos++;
			}
			ret = (char*)malloc(sizeof(char*)*(length + 8)); //add 1 for NULL and 7 for "String_\"\""
			strcpy(ret, "String ");
			strncat(ret, tk->token + start, length + 1);
			strcat(ret, "\0");
			tk->pos = tk->pos + 2;
			break;
		case '\'':
			length++;
			while ((tk->token[tk->pos + 1] != '\'') && tk->token[tk->pos] != '\0'){
				length++;
				tk->pos++;
			}
			ret = (char*)malloc(sizeof(char*)*(length + 8)); //add 1 for NULL and 7 for "String_\"\""
			strcpy(ret, "String ");
			strncat(ret, tk->token + start, length + 1);
			strcat(ret, "\0");
			tk->pos = tk->pos + 2;
			break;
		case '+':
			//Operators that start with +
			length++;
			if (tk->token[tk->pos + 1] == '+'){
				/* ++ */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 12));
				strcpy(ret, "Plusplus \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else if (tk->token[tk->pos + 1] == '='){
				/* += */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 14));
				strcpy(ret, "Plusequals \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else {
				/* + */
				ret = (char*)malloc(sizeof(char*)*(length + 8));
				strcpy(ret, "Plus \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos++;
				break;
			}
		case '-':
			//Operators that start with -
			length++;
			if (tk->token[tk->pos + 1] == '-'){
				/* -- */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 14));
				strcpy(ret, "Minusminus \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else if (tk->token[tk->pos + 1] == '='){
				/* -= */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 15));
				strcpy(ret, "Minusequals \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else if (tk->token[tk->pos + 1] == '>'){
				/* -> */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 18));
				strcpy(ret, "Struct Pointer \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else {
				/* - */
				ret = (char*)malloc(sizeof(char*)*(length + 8));
				strcpy(ret, "Minus \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos++;
				break;
			}
		case '*':
			//Operators that start with *
			length++;
			if (tk->token[tk->pos + 1] == '='){
				/* *= */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 15));
				strcpy(ret, "Timesequals \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else {
				/* * */
				ret = (char*)malloc(sizeof(char*)*(length + 12));
				strcpy(ret, "Multiply \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos++;
				break;
			}
		case '!':
			//Operators that start with !
			length++;
			if (tk->token[tk->pos + 1] == '='){
				/* != */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 12));
				strcpy(ret, "Notequals \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else {
				/* ! */
				ret = (char*)malloc(sizeof(char*)*(length + 7));
				strcpy(ret, "Not \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos++;
				break;
			}
		case '=':
			//Operators that start with =
			length++;
			if (tk->token[tk->pos + 1] == '='){
				/* == */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 17));
				strcpy(ret, "Booleanequals \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else {
				/* = */
				ret = (char*)malloc(sizeof(char*)*(length + 14));
				strcpy(ret, "Assignment \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos++;
				break;
			}
		case '%':
			//Operators that start with %
			length++;
			if (tk->token[tk->pos + 1] == '='){
				/* %= */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 16));
				strcpy(ret, "Moduloequals \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else {
				/* % */
				ret = (char*)malloc(sizeof(char*)*(length + 10));
				strcpy(ret, "Modulo \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos++;
				break;
			}
		case '^':
			//Operators that start with ^
			length++;
			if (tk->token[tk->pos + 1] == '='){
				/* ^= */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 13));
				strcpy(ret, "Xorequals \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else {
				/* ^ */
				ret = (char*)malloc(sizeof(char*)*(length + 16));
				strcpy(ret, "Exclusive Or \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos++;
				break;
			}
		case '&':
			//Operators that start with &
			length++;
			if (tk->token[tk->pos + 1] == '&'){
				/* && */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 15));
				strcpy(ret, "Boolean And \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else if (tk->token[tk->pos + 1] == '='){
				/* &= */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 13));
				strcpy(ret, "Andequals \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else {
				/* & */
				ret = (char*)malloc(sizeof(char*)*(length + 11));
				strcpy(ret, "Bit And \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos++;
				break;
			}
		case '|':
			//Operators that start with |
			length++;
			if (tk->token[tk->pos + 1] == '|'){
				/* || */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 14));
				strcpy(ret, "Boolean Or \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else if (tk->token[tk->pos + 1] == '='){
				/* |= */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 13));
				strcpy(ret, "Orequals \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else {
				/* | */
				ret = (char*)malloc(sizeof(char*)*(length + 10));
				strcpy(ret, "Bit Or \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos++;
				break;
			}
		case '<':
			//Operators that start with <
			length++;
			if ((tk->token[tk->pos + 1] == '<') && (tk->token[tk->pos + 2] == '=')){
				/* <<= */
				length += 2;
				ret = (char*)malloc(sizeof(char*)*(length + 20));
				strcpy(ret, "Left Shift Equal \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 3;
				break;
			}
			else if (tk->token[tk->pos + 1] == '='){
				/* <= */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 17));
				strcpy(ret, "Less or Equal \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else if (tk->token[tk->pos + 1] == '<'){
				/* << */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 14));
				strcpy(ret, "Left Shift \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else {
				/* < */
				ret = (char*)malloc(sizeof(char*)*(length + 13));
				strcpy(ret, "Less than \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos++;
				break;
			}
		case '>':
			//Operators that start with >
			length++;
			if ((tk->token[tk->pos + 1] == '>') && (tk->token[tk->pos + 2] == '=')){
				/* >>= */
				length += 2;
				ret = (char*)malloc(sizeof(char*)*(length + 21));
				strcpy(ret, "Right Shift Equal \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 3;
				break;
			}
			else if (tk->token[tk->pos + 1] == '='){
				/* >= */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 20));
				strcpy(ret, "Greater or Equal \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else if (tk->token[tk->pos + 1] == '>'){
				/* >> */
				length++;
				ret = (char*)malloc(sizeof(char*)*(length + 15));
				strcpy(ret, "Right Shift \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos = tk->pos + 2;
				break;
			}
			else {
				/* > */
				ret = (char*)malloc(sizeof(char*)*(length + 16));
				strcpy(ret, "Greater than \"");
				strncat(ret, tk->token + start, length);
				strcat(ret, "\"\0");
				tk->pos++;
				break;
			}
		case '~':
			/* ~ */
			length++;
			ret = (char*)malloc(sizeof(char*)*(length + 20));
			strcpy(ret, "One's Complement \"");
			strncat(ret, tk->token + start, length);
			strcat(ret, "\"\0");
			tk->pos++;
			break;
		case ',':
			/* , */
			length++;
			ret = (char*)malloc(sizeof(char*)*(length + 16));
			strcpy(ret, "Discard Left \"");
			strncat(ret, tk->token + start, length);
			strcat(ret, "\"\0");
			tk->pos++;
			break;
		case '[':
			/* [ */
			length++;
			ret = (char*)malloc(sizeof(char*)*(length + 14));
			strcpy(ret, "Left Brace \"");
			strncat(ret, tk->token + start, length);
			strcat(ret, "\"\0");
			tk->pos++;
			break;
		case ']':
			/* ] */
			length++;
			ret = (char*)malloc(sizeof(char*)*(length + 15));
			strcpy(ret, "Right Brace \"");
			strncat(ret, tk->token + start, length);
			strcat(ret, "\"\0");
			tk->pos++;
			break;
		case '(':
			/* ( */
			length++;
			ret = (char*)malloc(sizeof(char*)*(length + 14));
			strcpy(ret, "Open Paren \"");
			strncat(ret, tk->token + start, length);
			strcat(ret, "\"\0");
			tk->pos++;
			break;
		case ')':
			/* ) */
			length++;
			ret = (char*)malloc(sizeof(char*)*(length + 15));
			strcpy(ret, "Close Paren \"");
			strncat(ret, tk->token + start, length);
			strcat(ret, "\"\0");
			tk->pos++;
			break;
		case '{':
			/* { */
			length++;
			ret = (char*)malloc(sizeof(char*)*(length + 23));
			strcpy(ret, "Open Squiggly Brace \"");
			strncat(ret, tk->token + start, length);
			strcat(ret, "\"\0");
			tk->pos++;
			break;
		case '}':
			/* } */
			length++;
			ret = (char*)malloc(sizeof(char*)*(length + 24));
			strcpy(ret, "Close Squiggly Brace \"");
			strncat(ret, tk->token + start, length);
			strcat(ret, "\"\0");
			tk->pos++;
			break;
		case ';':
			/* ; */
			length++;
			ret = (char*)malloc(sizeof(char*)*(length + 13));
			strcpy(ret, "Semicolon \"");
			strncat(ret, tk->token + start, length);
			strcat(ret, "\"\0");
			tk->pos++;
			break;
		case '?':
			/* ?*/
			length++;
			ret = (char*)malloc(sizeof(char*)*(length + 17));
			strcpy(ret, "Question Mark \"");
			strncat(ret, tk->token + start, length);
			strcat(ret, "\"\0");
			tk->pos++;
			break;
		case ':':
			/* : */
			length++;
			ret = (char*)malloc(sizeof(char*)*(length + 9));
			strcpy(ret, "Colon \"");
			strncat(ret, tk->token + start, length);
			strcat(ret, "\"\0");
			tk->pos++;
			break;

		case '\0': tk->pos++; ret = NULL; break;
			/*Non-AlphaNumeric cases*/
		default:
			/*Unknown Characters*/			
			unkn = tk->token[tk->pos];
			hex = (unsigned int)unkn;
			sprintf(hchar, "%.2x", hex);

			ret = (char*)malloc(sizeof(char*)*(2 + 19));
			strcpy(ret, "Unknown Input [0x");
			strcat(ret, hchar);
			strcat(ret, "]\0");
			tk->pos++;
			//ret = TKGetNextToken(tk); break;
			/*This is a case we do not test for*/
		}
	}


	return ret;
}

/*
* main will have a string argument (in argv[1]).
* The string argument contains the tokens.
* Print out the tokens in the second string in left-to-right order.
* Each token should be printed on a separate line.
*/

int main(int argc, char **argv) {
	/*
	char* stream = "if auto break case char const continue default do double enum extern float for goto if int long register return short signed sizeof static struct typedef union unsigned void volatile while else if";// : 0023 \n 0xADFC \t edf98 h172678 ++Bobman Batman CaptMercua //This is a comment \n this is not \"This is a string in a quote\" \'this too\' + ++ += - -- -> -= * *=yup /hi /=wee ! != = == % %= ^ ^= & &= && | || |= < << <<= <= > >> >>= >= ~ , array[xyz ] function(int a) @ ? | ` *&^$%#^@%~!@#%*^&)(*&)@#!IOUKJGEDHSBFLIZUKHN{C(QPOU&*(*Y_(#*PIUOHRKJHF^*&(648793oij8";
	//char stream[] = "@";
	TokenizerT *tkStream = TKCreate(stream); //Initalize the TokenStream
	int length = strlen(tkStream->token);
	printf("%s\nStarting:\n", tkStream->token);
	*/

	//Input validation
		
	if (argc != 2){
		// input should include a string 
		printf("Error: Invalid number of arguments.\n");
		return 0;
	}
	

	//printf("%s\n", argv[1]); //Taken out for inline Testing
	TokenizerT *tkStream = TKCreate(argv[1]); //Initalize the TokenStream
	int length = strlen(tkStream->token);
	

	/*loop over TKGetNextToken*/
	char* tok = NULL;
	do{
		tok = TKGetNextToken(tkStream);
		if (tok != NULL)
			printf("%s\n", tok);
		free(tok);
	} while (tkStream->pos < length);

	TKDestroy(tkStream);
	return 0;
}