// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 1 : Exp 1 - Program No: (vi): Familiarization of execl() system call
// ADARSH P.K. CSU13203

#include <stdio.h>
#include <unistd.h>

void main()
{
	printf("Hi from source program %d and parent is %d\n",getpid(),getppid());
	fflush(stdout);
    execl("hello","hello",(char*)NULL);
    write(1," If this works it is an error",29);
}
