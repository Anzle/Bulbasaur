/* 
 * Robert Williams & Sangini Shah
 * main.c
 * using this site for System call information
 * http://codewiki.wikidot.com/system-calls
 * http://stackoverflow.com/questions/146924/how-can-i-tell-if-a-given-path-is-a-directory-or-a-file-c-c
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
#include <dirent.h>
#include <features.h>
#include "indexer.h"




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

/*
 * Tokenize the file with alphanumbric stuffz
 */
char * tokenize(input * iptr){
	
	int length = 0, size = 100;
	char * tok = NULL, * extend = NULL;
	char c;
	tok = (char*)calloc(sizeof(char)*(size + 1), 1);
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

/*
 * Recurse through the file structure and if the input is a file
 * tokenize the contents of the file
 * return 0 on success
 */
int fileRecurse(char * path, IndexerPtr indexMap){
    struct stat s;
    if( stat(path,&s) > -1 ){
        if( S_ISDIR(s.st_mode) ){
            printf("Location %s is a Directory\n", path);

            DIR *dp;
            struct dirent *ep;

            dp = opendir (path);
            if (dp != NULL){
                while ((ep = readdir (dp))){
                    if(strcmp(ep->d_name, "/..")==0 || strcmp(ep->d_name, "..")==0 || strcmp(ep->d_name, "/.")==0 || strcmp(ep->d_name, ".")==0)
                        continue;
                    //printf("%s \n",ep->d_name); //test directory walking
                   
                    if(strcmp(path, "./") == 0 || strcmp(path, ".") == 0){
                        fileRecurse(ep->d_name, indexMap);
                    }
                    else{
                        char* next = (char *) malloc(sizeof(char*)*(strlen(path)+strlen(ep->d_name)+2));
                        strcpy(next, path);
           
                        if(path[strlen(path)-1] != '/')
                            strcat(next, "/");
                        strcat(next, ep->d_name);
                       // free(path);
                        fileRecurse(next, indexMap);
                        
                    }
                    
                }
            
                (void) closedir (dp);
            }
            else
                perror ("Couldn't open the directory\n");

            return 0;
        }//END if Directory
        
        else if( S_ISREG(s.st_mode) ){
            if(strcmp(path, ".txt") == 0)
                return 0;
           printf("Location %s is a File\n", path);
            int filedesc = open(path, O_RDONLY);
            input * iptr = (input*)malloc(sizeof(input));

            resetInput(iptr, filedesc);
            char* tok = tokenize(iptr);
            while(tok){
				//printf("%s\n",tok);
                countToken(indexMap, tok, path);
                tok = tokenize(iptr);
            }
            //close(filedesc);
           // free(iptr);
            
            return 0;
        }//End if File
    }//end
    else{
        printf("Failed on string %s\n",path);
        return 1;
    }
    return 1;
 }   

int main(int argv, char ** argc){

    if(argv != 3)
        fprintf(stderr, "Use as follows: index <inverted-index> <directory/file>\n");
    
    //Open the directory/filename in read only format
   // int filedesc = open(argc[2], O_RDONLY);
	//int bufferSize = 2048;
    //if(filedesc < 0){
    //    fprintf(stderr, "There was an error obtaining the file descriptor from the Kernel \n");
   //     return 1;
   // }
	
	//Open the write file in write only format
	int writefd = open(argc[1], O_CREAT |O_WRONLY, S_IRUSR|S_IWUSR);
    if(writefd < 0){
		fprintf(stderr, "There was an error opening the index file.\n");
		return 1;
	}
	
	//Set up the input reading buffer
	//input * iptr = (input*)malloc(sizeof(input));
	//resetInput(iptr, filedesc);

	//Create indexer and insert tokens into it
	IndexerPtr indexMap = createIndexer();
	if(!indexMap){
		fprintf(stderr,"Error creating indexer\n");
		return 1;
	}
	
    if(fileRecurse(argc[2], indexMap) == 1){
        fprintf(stderr, "There was an error recursing the files\n");
        return 1;
    }
    
/* 	char* tok = tokenize(iptr);
	while (tok != NULL){
		//printf("%s \n", tok);
		char path[16] = {0};
		strcpy(path, "/proc/self/fd/");
		char fdesc[3] = {0};
		strcat(path, itobase10(fdesc, iptr->fd));
		//char fileName[100] ={0};
		//readlink(path, fileName, 100);  //this would be used to find the file name. 
										  //not sure how to make it work yet.
		countToken(indexMap, tok, argc[2]);
		tok = tokenize(iptr);
	} */
	
	char* json = (char*) malloc(80000000);
	memset(json, 0, 300000);
	toJSON(indexMap, json);
	if(json){
		if(write(writefd, json, strlen(json)) < 0){
			fprintf(stderr, "Error writing to output file.\n");
		//	close(iptr->fd);
			close(writefd);
		//	free(iptr);
			free(json);
			destroyIndexer(indexMap);
			return 1;
		}
		printf("Output written to file.\n");
	//	close(iptr->fd);
		close(writefd);
		//free(iptr);
		free(json);
		destroyIndexer(indexMap);
		return 0;
	}
	fprintf(stderr, "Error creating JSON string\n");
    
	//close(iptr->fd);
	close(writefd);
	//free(iptr);
	free(json);
	destroyIndexer(indexMap);
	return 1;
}