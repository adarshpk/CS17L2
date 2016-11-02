// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 1 : Exp 1 - Program No: (vii): Familiarization of wait() system call
// ADARSH P.K. CSU13203

#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main()
{
   pid_t pid1 = fork();
   pid_t pid;

   if (pid1 > 0) {
      pid_t pid2 = fork();      
   	  if (pid2 > 0)  {
        int status;
        printf(" Parent : Let the child processes complete.\n");
        pid = wait(&status);
        printf(" Parent : Child process %d has completed.\n", pid);
        pid = wait(&status);
        printf(" Parent : Child process %d has completed.\n", pid);
        printf(" Parent : Hello from the parent process!\n");
     }
     else if (pid2 == 0) {
      	printf(" Hello from the child process 1 (%d)!\n\n",getpid());
     }
     else if (pid2 == -1) {
      perror("Fork2 failed");
   	 }
   }
   else if (pid1 == -1) {
      perror("Fork1 failed");
   }
   else if (pid1 == 0) {
      printf(" Hello from the child process 2 (%d)!\n\n",getpid());
   }
   return 0;
}
