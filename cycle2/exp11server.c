// Date: 22/09/2016
// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 2 : Exp 11 - INTERPROCESS COMMUNICATION USING POSIX MESSAGE QUEUES
/* Implementing a token system using POSIX message queues. Program code for the
client that receives tokens from the server.
*/
// ADARSH P.K. CSU13203

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <mqueue.h>

#define SERVER_QUEUE_NAME   "/mq-server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main ()
{
    mqd_t qd_server, qd_client;   // queue descriptors
    long token_number = 1; // next token to be given to client
    printf ("Server: Hello, World!\n");
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        perror ("Server: mq_open (server)");
        exit (1);
    }
    char in_buffer [MSG_BUFFER_SIZE];
    char out_buffer [MSG_BUFFER_SIZE];

    while (1) {
        if (mq_receive (qd_server, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
            perror ("Server: mq_receive");
            exit (1);
        }
        printf ("Server: message received.\n");
        if ((qd_client = mq_open (in_buffer, O_WRONLY)) == 1) {
            perror ("Server: Not able to open client queue");
            continue;
        }
        sprintf (out_buffer, "%ld", token_number);
        if (mq_send (qd_client, out_buffer, strlen (out_buffer), 0) == -1) {
            perror ("Server: Not able to send message to client");
            continue;
        }
        printf ("Server: response sent to client.\n");
        token_number++;
    }
}