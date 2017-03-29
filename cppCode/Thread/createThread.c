#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <pthread.h>

void* Thread_functionWithCleanup(void * args) ;
void* Thread_function(void *args) ;
void* Thread_funtionWithCancelEnable(void * args) ;
void cleanup1(void *) ;
void cleanup2(void *) ;

int main()
{
	int *retval ;
	pthread_t thread1,thread2,thread3 ;
	pthread_create(&thread1,NULL,Thread_functionWithCleanup,NULL) ;
	pthread_create(&thread2,NULL,Thread_funtionWithCancelEnable,NULL) ;
	pthread_create(&thread3,NULL,Thread_function,&thread2) ;
	pthread_join(thread1,(void **)&retval) ;
	
	return 0 ;
}
void *Thread_functionWithCleanup(void * args)
{
	// register cleanup function
	pthread_cleanup_push(cleanup1,NULL) ;
	pthread_cleanup_push(cleanup2,NULL) ;
	
	// Do something
	printf("You are at thread_funtionWithCleanup!!\n") ;
	sleep(3) ;
	
	// in the end of thread function ,execute the cleanup function
	pthread_cleanup_pop(0) ; //0: indicates that do not execute the poped clean up function
	pthread_cleanup_pop(1) ; //non-zero : indicates thad execute the clean up funciton when it is poped from stack
	
	pthread_exit(0) ;

}
void *Thread_function(void *args)
{
	pthread_t *threadid = (pthread_t*)args ;
	pthread_detach(pthread_self()) ;// set thread to unjoinable status
	printf("You are in thread without cleanup, and this thread is unjoinable!\n") ;
	sleep(3) ;
	pthread_cancel(*threadid) ;
}
void* Thread_funtionWithCancelEnable(void * args)
{
	// set thread's cancel state
	// PTHREAD_CANCEL_ENABLE: thread can be canceled by other thread
	// PTHREAD_CANCEL_DISABLE: thread can not be canceled. 
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL) ;

	// set the cancel type of thread
	// PTHREAD_CANCEL_DEFERRED: the thread don't be canceled until it is go to canceled point.
	// PTHREAD_CANCEL_ASYNCHRONOUS: the thread can be canceld in any time.
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL) ; // this is system default behaviour!
	while(1)
	{
		printf(" wait to be canceled!\n") ;
		pthread_testcancel() ;  // this call can add a cancel point
		sleep(3) ;
	}
}
void cleanup1(void * args)
{
	printf("clean up 1 ....\n") ;
}
void cleanup2(void * args)
{
	printf("clean up 2 ....\n") ;
}
