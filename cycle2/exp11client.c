// Date: 22/09/2016
// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 2 : Exp 11 - INTERPROCESS COMMUNICATION USING POSIX MESSAGE QUEUES
/* Implementing a token system using POSIX message queues. Program code for the
server that generates tokens and sends it to the client.
*/
// ADARSH P.K. CSU13203

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <unistd.h>
#include <mqueue.h>

#define SERVER_QUEUE_NAME   "/mq-server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main ()
{
    char client_queue_name [64];
    mqd_t qd_server, qd_client;
    sprintf (client_queue_name, "/client-%d", getpid ());

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    if ((qd_client = mq_open (client_queue_name, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        perror ("Client: mq_open (client)");
        exit (1);
    }

    if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_WRONLY)) == -1) {
        perror ("Client: mq_open (server)");
        exit (1);
    }

    char in_buffer [MSG_BUFFER_SIZE];

    printf ("Ask for a token (Press <ENTER>): ");

    char temp_buf [10];

    while (fgets (temp_buf, 2, stdin)) {

        if (mq_send (qd_server, client_queue_name, strlen (client_queue_name), 0) == -1) {
            perror ("Client: Not able to send message to server");
            continue;
        }
        if (mq_receive (qd_client, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
            perror ("Client: mq_receive");
            exit (1);
        }
        // display token received from server
        printf ("Client: Token received from server: %s\n\n", in_buffer);

        printf ("Ask for a token (Press ): ");
    }
    if (mq_close (qd_client) == -1) {
        perror ("Client: mq_close");
        exit (1);
    }
    if (mq_unlink (client_queue_name) == -1) {
        perror ("Client: mq_unlink");
        exit (1);
    }
    printf ("Client: bye\n");

    exit (0);
}