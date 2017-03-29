#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>

void * signal_thread(void * args) ;
void * wait_thread(void * args) ;
pthread_cond_t cond ;
pthread_mutex_t mutex ;

int data = -1 ;

int main()
{
	pthread_cond_init(&cond,NULL) ;
	// cond = PTHREAD_COND_INITIALIZER
	pthread_mutex_init(&mutex,NULL) ;

	pthread_t sigThread,waitThread ;
	
	// create thread
	pthread_create(&sigThread,NULL, signal_thread,NULL) ;
	pthread_create(&waitThread,NULL,wait_thread,NULL) ;

	// join thread
	pthread_join(sigThread,NULL) ;
	pthread_join(waitThread,NULL) ;

	//destroy conditional variable
	pthread_cond_destroy(&cond) ;
	return 0;
}
void * signal_thread(void * args)
{
	int i = 0 ; 
	for(i = 0 ; i < 99 ; i++)
	{
		pthread_mutex_lock(&mutex) ;
		data ++ ;
		if(0 == data % 3)
			pthread_cond_signal(&cond) ;
		else
			printf("Signal thread: data %d\n",data) ;
		pthread_mutex_unlock(&mutex) ;
		
		sleep(1) ;
	}
}
void * wait_thread(void * args)
{
	int i = 0 ;
	while(i < 99)
	{
		pthread_mutex_lock(&mutex) ;
		if(0 != data%3)
			pthread_cond_wait(&cond,&mutex) ;
		printf("Wait Thread data : %d\n",data) ;
		pthread_mutex_unlock(&mutex) ;
		i++ ;
		sleep(1) ;
	}
}



