#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

void * read_thread(void * args) ;
void * write_thread(void * args) ;

int data = 0 ;
pthread_rwlock_t rwlock ;

int main()
{
	int i = 0 ;
	pthread_t readThread[10] ;
	pthread_t writeThread[3] ;

	pthread_rwlock_init(&rwlock,NULL) ;

	//create write thread
	for(i = 0 ;i < 3 ;i++)
	{
		pthread_create(&writeThread[i],NULL,write_thread,&i) ;
	} 

	// create read thread
	for(i = 0 ; i < 10 ; i++)
	{
		pthread_create(&readThread[i],NULL,read_thread,&i) ;
	}

	//wait write and read  thread to end.
	for(i = 0 ; i < 13 ;i ++)
	{
		if(i < 3)
			pthread_join(writeThread[i],NULL) ;
		else
			pthread_join(readThread[i-3],NULL) ;
	}
	//destroy reader-writer lock
	pthread_rwlock_destroy(&rwlock) ;
}

void * read_thread(void * args)
{
	int i = *((int *)args) ;
	pthread_rwlock_rdlock(&rwlock) ;
	printf("read thread %d print data: %d\n",i,data) ;
	pthread_rwlock_unlock(&rwlock) ;
	sleep(2) ;
	return ((void *)0) ;
}
void * write_thread(void * args)
{
	int i = *((int * )args) ;
	printf("write thread %d increase data's value!\n",i) ;
	pthread_rwlock_wrlock(&rwlock) ;
	data ++ ;
	pthread_rwlock_unlock(&rwlock) ;
	sleep(2) ;
	return ((void *)0) ;
}
