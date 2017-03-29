#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>

void * pthread_func(void * args) ;

int main()
{
	
	pthread_t thread ;
	sigset_t  signalset ;

	sigemptyset(&signalset) ;
	sigaddset(&signalset,SIGINT) ;
	sigaddset(&signalset,SIGQUIT) ;
	
	int s = pthread_sigmask(SIG_BLOCK,&signalset,NULL) ;

	pthread_create(&thread,NULL,pthread_func,&signalset) ;

	pthread_join(thread,NULL) ;
	

	return 0 ;
}
void * pthread_func(void * args)
{
	printf("thread starts to wait signal!...\n") ;
	sigset_t * set = (sigset_t *)args ;
	int ret,sigal ;
	while(1)
	{
		ret = sigwait(set,&sigal) ;
		if(ret < 0)
			break ;
		switch(sigal)
		{
		case SIGINT:
			printf("receive SIGINT!\n") ;
			pthread_exit(0) ;
			break ;
		case SIGQUIT:
			printf("receive SIGQUIT!\n") ;
			pthread_exit(0) ;			
			break ;
		}
	}
	return ((void *)0) ;
}
