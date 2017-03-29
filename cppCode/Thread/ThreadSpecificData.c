#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>

struct SpecificData
{
	int number ;
	char data[64] ;
};

pthread_once_t once = PTHREAD_ONCE_INIT ;
struct SpecificData data1,data2 ;
pthread_key_t key ;
void * thread_func(void * args) ;
void thread_init(); 
int main()
{
	pthread_t thread1,thread2 ;

	data1.number = 1 ;
	strcpy(data1.data,"I am data1!") ;
	data2.number = 2 ;
	strcpy(data2.data,"I am data2!") ;

	pthread_create(&thread1,NULL,thread_func,&data1) ;
	pthread_create(&thread2,NULL,thread_func,&data2) ;
	
	pthread_join(thread1,NULL) ;
	pthread_join(thread2,NULL) ;
	return 0 ;
}
void * thread_func(void * args)
{
	
	pthread_once(&once,thread_init) ;
	pthread_setspecific(key,args) ;

	// do somethings

	sleep(3) ;

	struct SpecificData *pData = (struct SpecificData *)pthread_getspecific(key) ;
	printf("SpecificData: number %d\n",pData->number) ;
	printf("SpecificData: data: %s\n",pData->data) ;
	
	
}
void thread_init()
{
	pthread_key_create(&key,NULL) ;
}
