/*
 *	indexer.c
 */

#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"
#include "indexer.h"

//Create new indexer object and return it 
IndexerPtr createIndexer(){
	IndexerPtr indexPtr = (IndexerPtr) malloc(sizeof(Indexer));
	if(!indexPtr)
		return NULL;
		
	memset(indexPtr, 0, sizeof(Indexer));
		
	return indexPtr;
}

//Free all data stored in the indexer
void destroyIndexer(IndexerPtr i){
	if(!i){
		return;
	}
	
	int x;
	for(x = 0; x<26; x++){
		if(i->index[x]){
			SLDestroy(i->index[x]);
		}
	}
	free(i);
}

int insertToken(IndexerPtr ind, const char* tok, const char* file, const int freq){
	if(!ind){
		return -1; //error, null indexer
	}
	
	//Create nodes and insert into the map
}


/*
 * Comparator function for FileNode. Compares based on frequency.
 * Returns 
 *		1 if f1.frequency > f2.frequency
 *		0 if 			  =
 *	   -1 if			  <
 */
int compareFileNode(void* f1, void* f2){
	
	if(!f1 || !f2){
		return -2;
	}
	
	FileNodePtr file1 = (FileNodePtr) f1;
	FileNodePtr file2 = (FileNodePtr) f2;
	
	if(file1->frequency < file2->frequency){
		return  -1;
	}
	else if(file1->frequency > file2->frequency){
		return 1;
	}
	else{
		return 0;
	}
	
}

/*
 *	Frees all memory associated with the FileNode
 */
void destroyFileNode(void* f){
	if(f)
		free(f);
}

/*
 * Comparator function for TokenNode. Compares based on ascii of token.
 * Returns 
 *		strcmp(t1.token, t2.token);
 */
int compareTokenNode(void* t1, void* t2){
	if(!t1 || !t2){
		return -2;
	}
	
	TokenNodePtr tok1 = (TokenNodePtr) t1;
	TokenNodePtr tok2 = (TokenNodePtr) t2;
	
	return strcomp(t1->token, t2->token);
}

/*
 *	Frees all memory associated with the TokenNode
 */
void destroyTokenNode(void* t){
	if(!t){
		return;
	}
	
	TokenNodePtr tok = (TokenNodePtr) t;
	
	SLDestroy(tok->files);
	free(tok);
}