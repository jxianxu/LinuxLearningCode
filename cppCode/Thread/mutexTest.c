#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>

void * write_thread(void * args) ;
void * read_thread(void * args) ;

int data = 0 ;
pthread_t threadWrite, threadRead ;
pthread_mutex_t mutex ;

int main()
{
	
	pthread_mutex_init(&mutex,NULL) ; // dynamic initialize
	// mutex = PTHREAD_MUTEX_INITIALIZER ; static initialize
	
	pthread_create(&threadWrite,NULL,write_thread,NULL) ;
	pthread_create(&threadRead,NULL,read_thread,NULL) ;
	pthread_join(threadWrite,NULL) ;
	pthread_join(threadRead,NULL) ;

	pthread_mutex_destroy(&mutex) ;
	return 0 ;
}
void * write_thread(void * args)
{
	int i = 0 ;
	printf("write thread is starting .....\n");
	
	for(i = 0 ; i < 100 ;i ++)
	{
		pthread_mutex_lock(&mutex) ;
		data ++ ;
		pthread_mutex_unlock(&mutex) ;
		sleep(2) ;
	} 
}
void * read_thread(void * args)
{
	int i = 0 ;
	printf("Read thread is starting.....\n") ;
	for(i = 0 ; i < 100 ; i++)
	{
		pthread_mutex_lock(&mutex) ;
		printf("data: %d\n", data) ;
		pthread_mutex_unlock(&mutex) ;
		sleep(2) ;
	}
}
