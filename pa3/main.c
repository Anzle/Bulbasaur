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

//#include "tok.h"

//Use Professor Rusle's code
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

int readinput(struct input* iptr, ){
	char c;
	if(iptr->used < iptr->length){
		c = iptr->buffer[iptr->used];
        iptr->used+=1;
        return c;
	}
    else if((iptr->length = read(iptr->fd, iptr->buffer, sizeof(iptr->buffer))) < 1){
        return -1
    }
    else{
        c = iptr->buffer[0];
        iptr->used = 1;
        return c;
    }
}


//Find the size of the file
off_t fsize(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    fprintf(stderr, "Cannot determine size of %s: %s\n", filename, strerror(errno));

    return -1;
}

int main(int argv, char ** argc){

    if(argv != 3)
        fprintf(stderr, "Use as follows: index <inverted-index> <directory/file>\n");
    
    //Open the directory/filename in read only format
    int filedesc = open(argc[2], O_RDONLY);
	int bufferSize = 2048;
    if(filedesc < 0){
        fprintf(stderr, "There was an error obtaining the file descriptor from the Kernel \n");
        return 1;
    }
    
	//Set up the input reading buffer
	input * iptr;
	resetInput(iptr, filedesc);
	
	//Determine the size of the file, I don't think we will have any files over 4 GB
	unsigned int filesize = (unsigned int)fsize(argc[2]);
	unsigned int i = 0;
	unsigned int block = filesize/bufferSize;
	for(i; i<block; i++){
		resetInput(iptr, filedesc);
		if(read(iptr->fd, iptr->buffer, bufferSize) < 0){
			 fprintf(stderr, "The read failed\n");
			 return 1;
		}
		int j = 0;
		while(j < 2048)
			printf("%c", iptr->buffer[j++]);
	}

    return 0;
}