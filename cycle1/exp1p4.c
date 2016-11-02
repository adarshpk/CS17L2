// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 1 : Exp 1 - Program No: (iv): Familiarization of pipe() system call
// ADARSH P.K. CSU13203

#include <unistd.h>

	int main()
	{
		int pid, pip[2];
		char data[20];

		pipe(pip); 

		pid = fork();
		if (pid == 0)    /* child : sends message to parent*/
		{
			close(pip[0]);
			/* send 7 characters in the string, including end-of-string */
			write(pip[1], "Hello!", 6);  
		}
		else			/* parent : receives message from child */
		{
			close(pip[1]);
			/* read from the pipe */
			read(pip[0], data, 6);
			write(1, data, 6);
		}
    }
