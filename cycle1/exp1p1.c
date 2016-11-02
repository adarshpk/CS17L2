// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 1 : Exp 1 - Program No: (i): Process ID and User ID
// ADARSH P.K. CSU13203

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	printf("\n\nProcess id: %d",getpid());
	printf("\nParent Process id: %d", getppid());
	printf("\nReal User id: %d", getuid());
	printf("\nEffective User id: %d", geteuid());
	printf("\nGroup id: %d", getgid());
	printf("\nEffective group id: %d", getegid());
	return 0;
}
