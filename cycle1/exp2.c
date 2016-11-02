// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 1 : Exp 2 - FILE TYPE
// ADARSH P.K. CSU13203

#include "sys/stat.h"
#include "stdio.h"
void main(int arc, char* argv[]) {
    struct stat status;
    lstat(argv[1],&status);
 	switch(status.st_mode & S_IFMT)
    {
    	case S_IFDIR:
        	printf("It is directory.\n");
			break;
    	case S_IFCHR:
        	printf("It is character file.\n");
			break;
        case S_IFLNK:
            printf("It is symbolic link.\n");
            break;
    	case S_IFREG:
        	printf("It is regular file.\n");
			break;
    	case S_IFBLK:
        	printf("It is block special file.\n");
			break;
    	case S_IFIFO:
        	printf("It is FIFO special file.\n");
			break;
        case S_IFSOCK:
            printf("It is a socket file.\n");
            break;  
	}
}

// Character file example : /dev/tty 
// Block special file example : /dev/sda