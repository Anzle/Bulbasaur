/*
 *	indexer.c
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "sorted-list.h"
#include "indexer.h"

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
	
	int result = strcmp(tok1->token, tok2->token);
	if(result > 0){
		return -1;
	}
	else if(result < 0){
		return 1;
	}
	else{
		return 0;
	}
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

//Creates and returns a TokenNodePtr. Returns null if error
TokenNodePtr createTokenNode(char * tok){
	if(!tok)
		return NULL;
		
	TokenNodePtr tkPtr = (TokenNodePtr) malloc(sizeof(TokenNode));
	if(!tkPtr)
		return NULL;
		
	tkPtr->token = tok;
	tkPtr->files = SLCreate(&compareFileNode, &destroyFileNode);
	if(tkPtr->files)
		return tkPtr;
		
	return NULL;
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

//Create new FileNodePtr and return it. Returns NULL on error
FileNodePtr createFileNode(char* name){
	if(!name)
		return NULL;
		
	FileNodePtr fileNode = (FileNodePtr) malloc(sizeof(FileNode));
	if(!fileNode)
		return NULL;
		
	fileNode->fileName = name;
	fileNode->frequency = 0;
	
	return fileNode;
} 

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

//converts an integer to its ascii equivalent
char *itobase10(char *buf, int value) {
    sprintf(buf, "%d", value);
    return buf;
}

//inserts or updates the token count
int countToken(IndexerPtr ind, char* tok, char* file){
	if(!ind){
		return -1; //error, null indexer
	}
	
	//Check if the token is already in the map. If not, create the node and insert it.
	//If so, check if the file is already in the map. If yes, update the count. If no,
	//create node and insert it into the list.
	int i=0;
	while(tok[i]){
		tok[i] = tolower(tok[i]);
		i++;
	}
	i = (int)(tok[0] -'a');
	SortedListPtr tokList = ind->index[i];
	
	if(!tokList){ //No tokens yet that start with this letter
		ind->index[i] = SLCreate(&compareTokenNode, &destroyTokenNode);
		
		TokenNodePtr tkPtr = createTokenNode(tok);
		if(!tkPtr){
			return -1;
		}
		
		tkPtr->files = SLCreate(&compareFileNode, &destroyFileNode);
		if(!tkPtr->files){
			return -1;
		}
		
		//Create fileNode for the given tokenNode
		FileNodePtr fPtr = createFileNode(file);
		if(!fPtr){
			return -1;
		}
		fPtr->frequency++; //update the frequency count for the token in the file
		
		SLInsert(tkPtr->files, fPtr); //insert the file into the token list		
		SLInsert(ind->index[i], tkPtr); //insert token into map
		return 0;
	}
	else { //tokens starting with that letter exist
		
		//check to see if given token is in the list
		SortedListIteratorPtr tokIter = SLCreateIterator(tokList);
		if(!tokIter)
			return -1;
			
		TokenNodePtr tokNode = (TokenNodePtr) SLGetItem(tokIter);
		while(tokNode){
			if(strcmp(tokNode->token, tok) == 0){
				break;
			}
			tokNode = (TokenNodePtr) SLNextItem(tokIter);
		}
		SLDestroyIterator(tokIter);
		
		if(!tokNode){ //token not in list. create new token node and insert into map
			TokenNodePtr tkPtr = createTokenNode(tok);
			if(!tkPtr){
				return -1;
			}
			
			tkPtr->files = SLCreate(&compareFileNode, &destroyFileNode);
			if(!tkPtr->files){
				return -1;
			}
			
			//Create fileNode for the given tokenNode
			FileNodePtr fPtr = createFileNode(file);
			if(!fPtr){
				return -1;
			}
			fPtr->frequency++; //update the frequency count for the token in the file
			
			SLInsert(tkPtr->files, fPtr); //insert the file into the token list		
			SLInsert(ind->index[i], tkPtr); //insert token into map
			return 0;
		}else{ //token in list. check for file
			
			SortedListIteratorPtr fileIter = SLCreateIterator(tokNode->files);
			if(!fileIter)
				return -1;
			
			FileNodePtr fileNode = (FileNodePtr) SLGetItem(fileIter);
			while(fileNode){
				if(strcmp(fileNode->fileName, file) == 0){
					break;
				}
				fileNode = (FileNodePtr) SLNextItem(fileIter);
			}
			SLDestroyIterator(fileIter);
			
			if(fileNode){ //file in list, increment count
				fileNode->frequency++;
				//SORT LATER
				return 0;
			} else { //file not in list. create new node and insert
				fileNode = createFileNode(file);
				if(!fileNode){
					return -1;
				}
				fileNode->frequency++; //update the frequency count for the token in the file
				
				SLInsert(tokNode->files, fileNode); //insert the file into the token list
				return 0;
			}
		}
		return -1;
	}
}

//returns a string of the JSON output
void toJSON(struct Indexer* ind, char* json){
	if(!ind || !json){
		return;
	}
	
	strcpy(json,"{\"list\" : [\n");
	int x;
	for(x = 0; x < 26; x++){
		if(ind->index[x] != NULL){
			SortedListIteratorPtr iterTok = SLCreateIterator(ind->index[x]);
			TokenNodePtr tokNode = (TokenNodePtr) SLGetItem(iterTok);
			
			while(tokNode){
				strcat(json, "\t{\"");
				strcat(json, tokNode->token);
				strcat(json, "\" : [\n");
				
				SortedListIteratorPtr iterFile = SLCreateIterator(tokNode->files);
				FileNodePtr fileNode = (FileNodePtr) SLGetItem(iterFile);
				
				strcat(json, "\t\t{\"");
				strcat(json, fileNode->fileName);
				strcat(json, "\" : ");
				char num[5] = {0};
				strcat(json, itobase10(num, fileNode->frequency));
				strcat(json, "}");
				
				fileNode = (FileNodePtr) SLNextItem(iterFile);
				while(fileNode){
					strcat(json, ",\n");
					strcat(json, "\t\t{\"");
					strcat(json, fileNode->fileName);
					strcat(json, "\" : ");
					char num1[5] = {0};
					strcat(json, itobase10(num1, fileNode->frequency));
					strcat(json, "}");
					fileNode = (FileNodePtr) SLNextItem(iterFile);
				}
				strcat(json,"\n\t]},\n");
				tokNode = (TokenNodePtr) SLNextItem(iterTok);
			}
		}
	}
	strcat(json,"]}\n\0");
}