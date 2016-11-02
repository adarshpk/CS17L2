// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 3 : Exp 15 : TCP CLIENT SERVER
// ADARSH P.K. CSU13203
/* Client Program for the chat function. It has to the server using the serve's IP address
*/
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <arpa/inet.h>

void *receiveMessage(void * socket) {
 int sockfd, ret;
 char buffer[1024]; 
 sockfd = (int) socket;
 memset(buffer, 0, 1024);  
 for (;;) {
  ret = recvfrom(sockfd, buffer, 1024, 0, NULL, NULL);  
  if (ret < 0) {  
   printf("Error receiving data!\n");    
  } else {
   if(!strcmp(buffer,"Quit\n"))
      exit(0);
    printf("Server: ");
   fputs(buffer, stdout);
   //printf("\n");
  }  
 }
}

int main(int argc, char* argv[]){
  int ret;
  pthread_t rThread;
  int clientSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7581);
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
  // recv(clientSocket, buffer, 1024, 0);
  // printf("Data received: %s",buffer);   
  ret = pthread_create(&rThread, NULL, receiveMessage, (void *) clientSocket);
  while (fgets(buffer, 1024, stdin) != NULL) {
  ret = sendto(clientSocket, buffer, 1024, 0, (struct sockaddr *) &serverAddr, addr_size);  
  if (ret < 0) {  
   printf("Error sending data!\n");  
   exit(1);
  }
  if(!strcmp(buffer,"Quit\n"))
      exit(0);
 } 
  return 0;
}