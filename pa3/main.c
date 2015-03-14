/* 
 * Robert Williams & Sangini Shah
 * main.c
 * using this site for System call information
 * http://codewiki.wikidot.com/system-calls
 *
 * Recurse through a file/directory and do the thing
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "indexer.h"
//#include "tok.h"

//Use Professor Russell's code
struct input{
	int		fd;
	int		length;
	int		used;
	char	buffer[2048];
};
typedef struct input input;


void resetInput(struct input* iptr , int fd){
	iptr->fd = fd;
	iptr->used = 0;
	iptr->length = 0;
}

int readInput(struct input* iptr){
	char c;
	if(iptr->used < iptr->length){
		c = iptr->buffer[iptr->used];
        iptr->used+=1;
        return c;
	}
    else if((iptr->length = read(iptr->fd, iptr->buffer, sizeof(iptr->buffer))) < 1){
        return -1;
    }
    else{
        c = iptr->buffer[0];
        iptr->used = 1;
        return c;
    }
}

char * tokenize(input * iptr){
	
	int length = 0, size = 100;
	char * tok = NULL, * extend = NULL;
	char c;
	tok = (char*)malloc(sizeof(char)*(size + 1));
	tok[size] = '\0'; //counts as a string now
	
	//Loop until we create a token
	while((c = readInput(iptr)) > -1){ 
		if (isalpha((char)c)){
			tok[length++] = c;
			while (isalnum((char)(c = readInput(iptr))) ){
				tok[length++] = (char)c;
				
				if(length == size){
					//increase the size of the string
					size += 100;
					extend = (char*)malloc(sizeof(char)*(size + 1));
					strcpy(extend, tok);
					extend[size] = '\0';
					
					free(tok);
					
					tok = extend;
					extend = NULL;
				}
			}
			
			int i=0; 
			while(i<length){
				tok[i] = tolower(tok[i]);
				i++;
			}
			return tok;
		}
	}
	//No more tokens... or failure
	//get rid of unused malloc
	free(tok);
	return NULL;
}

int main(int argv, char ** argc){

    if(argv != 3)
        fprintf(stderr, "Use as follows: index <inverted-index> <directory/file>\n");
    
    //Open the directory/filename in read only format
    int filedesc = open(argc[2], O_RDONLY);
	//int bufferSize = 2048;
    if(filedesc < 0){
        fprintf(stderr, "There was an error obtaining the file descriptor from the Kernel \n");
        return 1;
    }
    
	//Set up the input reading buffer
	input * iptr = (input*)malloc(sizeof(input));
	resetInput(iptr, filedesc);

	//Create indexer and insert tokens into it
	IndexerPtr indexMap = createIndexer();
	if(!indexMap){
		fprintf(stderr,"Error creating indexer\n");
		return 1;
	}
	
	char* tok = tokenize(iptr);
	while (tok != NULL){
		printf("%s \n", tok);
		char path[16] = {0};
		strcpy(path, "/proc/self/fd/");
		char fdesc[3] = {0};
		strcat(path, itobase10(fdesc, iptr->fd));
		//char fileName[100] ={0};
		//readlink(path, fileName, 100);  //this would be used to find the file name. 
										  //not sure how to make it work yet.
		countToken(indexMap, tok, argc[2]);
		tok = tokenize(iptr);
	}
	
	char* json = (char*) malloc(30000);
	memset(json, 0, 30000);
	toJSON(indexMap, json);
	printf("%s",json);
	
	free(iptr);
	destroyIndexer(indexMap);
	
    return 0;
}