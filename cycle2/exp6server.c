// Date: 06/09/2016
// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 2 : Exp 6 - INTERPROCESS COMMUNICATION USING FIFO
// Server program that accepts data sent by the client and diplays it.
// ADARSH P.K. CSU13203

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main()
{
    char in[100];
    mkfifo("csfifo", 0666);
    printf("Welcome to server.\n");
    printf("Channel for sending messages to server is %s\n", "csfifo");
    int in_fd=open("csfifo", O_RDONLY);
    if (in_fd==-1) {
        perror("open error");
        exit(-1);
    }
    while (read(in_fd, in, 100)>0) {
        printf("You sent %s to server.\n", in);
    }
    return 2;
}