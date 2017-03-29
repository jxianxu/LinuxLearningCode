#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

pthread_barrier_t barrier ;

void * sort_thread(void * args) ;
void mergeSort() ;
int main()
{
	int i= 0 ;
	pthread_t sortThread[10] ;

	//initialize barrier
	pthread_barrier_init(&barrier,NULL, 11) ;

	for(i = 0 ;i < 10 ; i++)
	{
		pthread_create(&sortThread[i],NULL,sort_thread,NULL) ;
	}
	
	pthread_barrier_wait(&barrier) ;
	mergeSort() ;
	printf("merge sort has been completed!\n") ;
	for(i = 0 ;i < 10 ; i++)
	{
		pthread_join(sortThread[i],NULL) ;
	}
	
	// remember to destroy the barrier
	pthread_barrier_destroy(&barrier) ;

	return 0 ;
}
void * sort_thread(void * args)
{
	// do some thing such as sort
	sleep(3) ;
	printf("I have completed the sort work!\n") ;
	pthread_barrier_wait(&barrier) ;
	sleep(4) ;
	return ((void *)0) ;
}
void mergeSort()
{
	// do something such as merge
	printf("Main Thread: I start to merge now!\n") ;
	sleep(2) ;
}

