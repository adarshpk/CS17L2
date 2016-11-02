// Date: 06/09/2016
// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 2 : Exp 6 - INTERPROCESS COMMUNICATION USING FIFO
// Client program that sends data to the server.
// ADARSH P.K. CSU13203

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char input[100]={0};
    int out_fd=open("csfifo", O_WRONLY);
    if (out_fd==-1) {
        perror("open error");
    }
    while (1) {
        printf("What would you like to send to server? (send Quit to quit)\n");
        fgets(input, 100, stdin);
        input[strlen(input)-1]='\0';
        if (strcmp(input, "Quit")==0) {
            printf("Bye!\n");
            break;
        }
        if (write(out_fd, input, strlen(input))==-1) {
            perror("write error");
        }
        fflush(stdin);
    }
    return 1;
}