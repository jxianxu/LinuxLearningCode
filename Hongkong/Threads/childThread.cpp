#include "childThread.h"
void ChildThread::Execute(void)
{
	int i = 0 ;
	for(i = 0 ; i < 10 ; i++)
	{
		printf("I am child thread !\n") ;
		sleep(1) ;
		data ++ ;
	}
} 
	
void ChildThread::ThreadContextInit(void)
{
	printf("child: do threadContext intialization!\n") ;
}
void ChildThread::ThreadContextDestroy(void)
{
	printf("child: do threadContext destroy!\n") ;
}
void ChildThread::Display()
{
	printf("data: %d\n",data) ;
}

