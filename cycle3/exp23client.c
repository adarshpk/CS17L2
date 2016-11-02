// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 3 : Exp 16 : UDP CLIENT SERVER
// ADARSH P.K. CSU13203
/* Client Program for the sequential chat function. It has to the server using the serve's IP address.
*/

#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 80
#define SA struct sockaddr

int main(int argc, char* argv[])
{
  char buff[MAX];
  int sockfd,len,n;
  struct sockaddr_in servaddr;
  sockfd=socket(AF_INET,SOCK_DGRAM,0);
  if(sockfd==-1)
  {
    printf("socket creation failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully created..\n");
  bzero(&servaddr,sizeof(len));
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=inet_addr(argv[1]);
  servaddr.sin_port=htons(7561);
  len=sizeof(servaddr);
  for(;;)
  {
    printf("Enter string : ");
    n=0;
    while((buff[n++]=getchar())!='\n');
      sendto(sockfd,buff,sizeof(buff),0,(SA *)&servaddr,len);
    bzero(buff,sizeof(buff));
    recvfrom(sockfd,buff,sizeof(buff),0,(SA *)&servaddr,&len);
    printf("From Server : %s",buff);
    if(strncmp("exit",buff,4)==0)
    {
      printf("Client Exit...\n");
      break;
    }
  }
  close(sockfd);
}