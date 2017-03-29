#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>
#include <stdbool.h>
#define MSG_MAX 164
struct Message
{
	long int msg_type ;
	char msg_data[MSG_MAX] ;
}; 

int main()
{
	bool isRuning  = true ;
	struct Message msg ;
	
	int msgid = 0 ;
	int msg_type = 1 ;

	msgid = msgget((key_t)123,0666| IPC_CREAT) ;
	if(msgid < 0)
	{
		printf("create msgQueue failed!\n") ;
		exit(0) ;
	}
	while(isRuning)
	{
		if(-1 == msgrcv(msgid,(void *)&msg,MSG_MAX,msg_type,0))
		{
			printf("msgrcv failed!\n") ;
			break ;
		}
		printf("I receive data: %s\n",msg.msg_data);
		if(0 == strncmp(msg.msg_data,"end",3))
		{
			printf("The data is end!\n") ;
			isRuning = false ;
		}
	}
	if(-1 == msgctl(msgid,IPC_RMID,0))
	{
		printf(" delete msgQueue failed!\n") ;
	}
	return 0 ;
}
