// Date: 06/09/2016
// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 2 : Exp 6 - INTERPROCESS COMMUNICATION USING PIPES
/* Parent sends the process id of the child to the child process.
The child receives the id decrements it by one, sends it back to the parent.
*/
// ADARSH P.K. CSU13203

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
	int p1[2],p2[2];
	pipe(p1);
 	pipe(p2);
 	pid_t a=fork();
	if(a==0)
 	{
 		close(p1[0]);
 		close(p2[1]);
 		printf("\nChild %d says hi!",getpid());
 		read(p2[0],&a,sizeof(a));
 		printf("\nChild Received : %d\n",a--);
 		write(p1[1],&a,sizeof(a));

 	}
 	else
 	{
 		close(p1[1]);
 		close(p2[0]);
 		write(p2[1],&a,sizeof(a));
 		printf("\nParent %d says hi!",getpid());
 		read(p1[0],&a,sizeof(a));
 		printf("\nParent Received : %d\n",a);
	}
	return 0;
}