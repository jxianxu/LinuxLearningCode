#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>

void * threadfunc(void * args)
{
	printf("thread is starting!\n") ;
	sleep(7) ;
	return ((void *)0) ;
}

int main()
{
	pthread_attr_t attr ;
	pthread_t thread_id ;

	int detachstate = 0 ;
	size_t guardsize = 0 ;
	size_t stacksize = 0 ;
	void * stackaddr = NULL ;

	pthread_attr_init(&attr) ;
	pthread_create(&thread_id,&attr,threadfunc,NULL) ;
	pthread_attr_getdetachstate(&attr,&detachstate) ;
	pthread_attr_getguardsize(&attr,&guardsize) ;
	pthread_attr_getstack(&attr,&stackaddr,&stacksize) ;
	printf("detachstate: %d\n",detachstate);
	printf("guardsize: %d\n",guardsize) ;
	printf("stackaddr: %08X\n",*((int*)stackaddr)) ;
	printf("stacksize: %d\n",stacksize) ;
	pthread_join(thread_id,NULL) ;
	
	return 0;
}
