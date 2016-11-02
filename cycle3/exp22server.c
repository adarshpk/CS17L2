// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 3 : Exp 15 : TCP CLIENT SERVER
// ADARSH P.K. CSU13203
// Server Program for the chat function.

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <arpa/inet.h>

void * receiveMessage(void * socket) {
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
  printf("Client: ");
   fputs(buffer, stdout);
   //printf("\n");
  }  
 }
}

int main(int argc, char* argv[]){
  int ret;
  pthread_t rThread;
  int welcomeSocket, newSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7581);
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  
  if(listen(welcomeSocket,5)==0)
    printf("Chat Session Established. Server Listening.\n");
  else
    printf("Error\n");
  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  ret = pthread_create(&rThread, NULL, receiveMessage, (void *) newSocket);
  // while(1)
  // {
  //   fgets(buffer,sizeof(buffer),stdin);
  //   if(strcmp(buffer,"Quit"))
  //     send(newSocket,buffer,sizeof(buffer),0);
  //   else
  //     break;
  // }
  while (fgets(buffer, 1024, stdin) != NULL) {
  ret = sendto(newSocket, buffer, 1024, 0, (struct sockaddr *) &serverStorage, addr_size);  
  if (ret < 0) {  
   printf("Error sending data!\n");  
   exit(1);
  }
  if(!strcmp(buffer,"Quit\n"))
      exit(0);
 } 
  shutdown(welcomeSocket,SHUT_RDWR);
  pthread_exit(NULL);

  return 0;
}