// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 1 : Exp 1 - Program No: (v): To create a FIFO (named pipe)
// ADARSH P.K. CSU13203

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void main()
{
	char buff[50]="This is being read from a FIFO file\n";
	char b[50];
	mkfifo("fifo1",0777);
	int fd=open("fifo1",2);
	pid_t k=fork();
	if(k==0)
	{
		write(1," Child process Done \n\n",22);
		write(fd,buff,50);
		printf("\n");
	}
	else
	{
		read(fd,b,50);
		write(1," Parent process : ",18);
		write(1,b,50);
		printf("\n");
	}
	close(fd);
}
