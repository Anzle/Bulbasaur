#ifndef INDEXER_H
#define INDEXER_H
/*
 *	indexer.h
 */

#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"

/*
 *	Indexer type. Hashmap that holds a list called index of SortedListPtrs. 
 *	Each list in the Indexer will hold the tokens and their corresponding data values. 
 *	These lists will be sorted by ascii alphabetical order.
 */
typedef struct Indexer {
	SortedListPtr index[26];
} Indexer;
typedef struct Indexer* IndexerPtr;

/*
 *	TokenNode type. This node holds the token name and a SortedList, files, which will
 * 	hold FileNodes that indicate what files hold the specific token and how often they 
 *	appear in the file. files will be sorted based on the frequency count of the token.
 */
typedef struct TokenNode{
	char* token;
	SortedListPtr files;
} TokenNode;
typedef struct TokenNode* TokenNodePtr;

/*
 *	FileNode type. This node holds the file name and the frequency with with the token
 *	is found in the file. 
 */
typedef struct FileNode{
	char* fileName;
	int frequency;
} FileNode;
typedef struct FileNode* FileNodePtr;

//Create new FileNodePtr and return it. Returns NULL on error
FileNodePtr createFileNode(char* name);

/*
 * Comparator function for FileNode. Compares based on frequency.
 * Returns 
 *		1 if f1.frequency > f2.frequency
 *		0 if 			  =
 *	   -1 if			  <
 */
int compareFileNode(void* f1, void* f2);

/*
 *	Frees all memory associated with the FileNode
 */
void destroyFileNode(void* f);

//Creates and returns a TokenNodePtr. Returns null if error
TokenNodePtr createTokenNode(char * tok);

/*
 * Comparator function for TokenNode. Compares based on ascii of token.
 * Returns 
 *		strcmp(t1.token, t2.token);
 */
int compareTokenNode(void* t1, void* t2);

/*
 *	Frees all memory associated with the TokenNode
 */
void destroyTokenNode(void* t);

//Create new indexer object and return it 
IndexerPtr createIndexer();

//converts an integer to its ascii equivalent
char *itobase10(char *buf, int value);

//inserts or updates the token count
int countToken(IndexerPtr ind, char* tok, char* file);

//Free all data stored in the indexer
void destroyIndexer(IndexerPtr i);

/*
 *	Returns JSON string of the map
 */
 void toJSON(struct Indexer*, char*);
#endif