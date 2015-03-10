/* 
 * Robert Williams & Sangini Shah
 * main.c
 * using this site for System call information
 * http://codewiki.wikidot.com/system-calls
 *
 * Recurse through a file/directory and do the thing
*/
#include<stdio>
#include<fstream>


#include <fcntl.h> //Used for open System Call 
/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>
/*I really don't know if we need the above. Will run on iLabs later*/


int main(int argv, char ** argc){

    if(argv != 3)
        fprintf(stderr, "Use as follows: index <inverted-index> <directory/file>\n");
    
    //Open the directory/filename in read only format
    int filedesc = open(argc[2], O_RDONLY);

    if(filedesc < 0){
        fprintf(stderr, "There was an error obtaining the file descriptor from the Kernal \n");
        return 1;
    }
        
    
    
    return 0;
}