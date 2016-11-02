// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 1 : Exp 1 - Program No: (iii): Familiarization of system() system call
// ADARSH P.K. CSU13203

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char * argv[])
{
   char command[50];
   strcpy(command, argv[1]);
   system(command);
   return(0);
} 
