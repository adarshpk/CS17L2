// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 1 : Exp 4 - STUDY OF SIGNALS.
// ADARSH P.K. CSU13203

#include <stdio.h>
#include <signal.h>
 
void sigproc(void);
void display_message(void);
void quitproc(void); 
 
main()
{	
 		signal(SIGALRM, display_message);
    	alarm(5);
		signal(SIGINT, sigproc);
		signal(SIGQUIT, quitproc);
		printf("Ctrl+c is temporarily disabled. Use Ctrl+\\ to quit.\n");
		for(;;); /* infinite loop */
 		
}

void sigproc()
{ 
		 signal(SIGINT, SIG_DFL); 
		 /* NOTE some versions of UNIX will reset signal to default
		 after each call. So for portability reset signal each time */
		 printf("You have pressed Ctrl+c. Press Ctrl+c again to terminate the process.\n");
}

void display_message()
{
	//signal(SIGINT, sigproc);
	//signal(SIGQUIT, quitproc);
	printf("Waiting...\n");
	alarm(3);
    //signal(SIGALRM, display_message);
}
 
void quitproc()
{ 		 printf("Ctrl+\\ pressed to quit\n");
		 exit(0); /* normal exit status */
}