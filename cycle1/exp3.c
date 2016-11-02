// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 1 : Exp 3 - FILE ATTRIBUTES
// ADARSH P.K. CSU13203

#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

int main ( int argc, char *argv[])
{
    struct stat FileAttrib;
    stat(argv[1], &FileAttrib);
    printf( "Access permissions: ");
    printf( (FileAttrib.st_mode & S_IRUSR) ? "r" : "-");
    printf( (FileAttrib.st_mode & S_IWUSR) ? "w" : "-");
    printf( (FileAttrib.st_mode & S_IXUSR) ? "x" : "-");
    printf( (FileAttrib.st_mode & S_IRGRP) ? "r" : "-");
    printf( (FileAttrib.st_mode & S_IWGRP) ? "w" : "-");
    printf( (FileAttrib.st_mode & S_IXGRP) ? "x" : "-");
    printf( (FileAttrib.st_mode & S_IROTH) ? "r" : "-");
    printf( (FileAttrib.st_mode & S_IWOTH) ? "w" : "-");
    printf( (FileAttrib.st_mode & S_IXOTH) ? "x" : "-");
    printf( "\ni-node number: %ld\n", FileAttrib.st_ino );
    printf( "Time of last file access: %s", asctime(localtime(&FileAttrib.st_atime)) );
    printf( "Time of last file modification: %s", asctime(localtime(&FileAttrib.st_mtime)) );
    printf( "File Size: %ld bytes.\n", FileAttrib.st_size );
    return 0;
}

// struct tm {
//    int tm_sec;         /* seconds,  range 0 to 59          */
//    int tm_min;         /* minutes, range 0 to 59           */
//    int tm_hour;        /* hours, range 0 to 23             */
//    int tm_mday;        /* day of the month, range 1 to 31  */
//    int tm_mon;         /* month, range 0 to 11             */
//    int tm_year;        /* The number of years since 1900   */
//    int tm_wday;        /* day of the week, range 0 to 6    */
//    int tm_yday;        /* day in the year, range 0 to 365  */
//    int tm_isdst;       /* daylight saving time             */	
// };

// struct tm *localtime(const time_t *timer)
// char* asctime (const struct tm * timeptr);

// void strmode(mode_t m, char *p);

// File mode bits:

// S_IRWXU
// Read, write, execute/search by owner.
// S_IRUSR
// Read permission, owner.
// S_IWUSR
// Write permission, owner.
// S_IXUSR
// Execute/search permission, owner.
// S_IRWXG
// Read, write, execute/search by group.
// S_IRGRP
// Read permission, group.
// S_IWGRP
// Write permission, group.
// S_IXGRP
// Execute/search permission, group.
// S_IRWXO
// Read, write, execute/search by others.
// S_IROTH
// Read permission, others.
// S_IWOTH
// Write permission, others.
// S_IXOTH