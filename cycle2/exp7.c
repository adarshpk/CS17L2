// Date: 06/09/2016
// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 2 : Exp 7 - FAMILIARISATION OF POSIX THREAD FUNCTIONS
/* Create two threads, one performing bubble sort on an array in ascending order
while the other performs selection sort on a copy of the same in descending order.
Both threads are joined to display the result. Also, a detached thread prints text.
*/
// ADARSH P.K. CSU13203

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
void *bubble_sort(void *arr1)
{
	printf("\nBubble Sort in ascending order initiated by thread %lu.\n", pthread_self());
	int *array = arr1; 
	int m,n,swap; 
	for (m=1; m<array[0]; m++)
    	for (n=1; n<=array[0]-m; n++)
    	{
      		if (array[n] > array[n+1])
      		{
        		swap       = array[n];
        		array[n]   = array[n+1];
        		array[n+1] = swap;
      		}
    	}
}

void *display_msg()
{
	printf("\nThis is printed from a detached thread! \n\n");
	fflush(stdout);
	pthread_exit(NULL);
}

int main()
{
	int i,j,swap,arr[101],dup[101],len, position;
	printf("Enter size of the array: ");
	scanf("%d", &arr[0]);
	dup[0]=arr[0];
	printf("Enter the array: ");
	for(i=1;i<=arr[0];i++) {
		scanf("%d", &arr[i]);
		dup[i]=arr[i];
	}
	pthread_t sec_thread;
	if(pthread_create(&sec_thread, NULL, bubble_sort, arr)) {
		fprintf(stderr, "Error creating thread 2\n");
		return 1;
	}
 	printf("\nSelection Sort in descending order initiated by thread %lu.\n", pthread_self());
 	for (i=1; i<dup[0]; i++)
   	{
    	position = i;
      	for (j=i+1; j<=dup[0]; j++)
      	{
         	if(dup[position]<dup[j])
            	position = j;
      	}
      	if (position!= i)
      	{
        	swap = dup[i];
         	dup[i] = dup[position];
         	dup[position] = swap;
      	}
   	}
 
	pthread_join(sec_thread, NULL);

	pthread_t third_thread;
	if(pthread_create(&third_thread, NULL, display_msg, NULL)) {
		fprintf(stderr, "Error creating thread 3\n");
		return 1;
	}
	pthread_detach(third_thread);
	sleep(2);
	printf("First Thread sorted the array in descending order:\n");
 
  	for(i=1; i<=dup[0]; i++)
    	printf("%d\n", dup[i]);

    printf("Second Thread sorted the array in ascending order:\n");
 
  	for(i=1; i<=arr[0]; i++)
    	printf("%d\n", arr[i]);
  	return 0;
}