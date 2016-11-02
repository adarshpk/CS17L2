// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 1 : Exp 1 - Program No: (ii): Familiarization of fork() system call
// ADARSH P.K. CSU13203

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
   pid_t pid = fork();

   if (pid > 0) {
        printf("\n Parent : Hello from the parent process (%d)!\n", getpid());
   }
   else if (pid == -1) {
      perror(" Fork failed");
   }
   else if (pid == 0) {
      printf(" Child : Hello from the child process (%d)!\n",getpid());
   }
   return 0;
}
