#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>

#define MSG_MAX 164
struct Message
{
	long int msg_type ;
	char msg_data[MSG_MAX] ;
};

int main()
{
	int msgid = 0 ;
	struct Message msg ;
	bool isRuning = true ;
	char buf[MSG_MAX] = {0} ;
	msgid = msgget((key_t)123,0666|IPC_CREAT) ;
	if(-1 == msgid)
	{
		printf("Create msgQueue failed!\n") ;
		exit(0) ;
	}
	
	while(isRuning)
	{
		printf("Please type the data to send: \n") ;
		fgets(buf,MSG_MAX,stdin) ;
		msg.msg_type = 1 ;
		strcpy(msg.msg_data,buf) ;
		if(-1 == msgsnd(msgid,(void*)&msg,MSG_MAX,0))
		{
			printf("msgsnd error!\n") ;
			exit(0) ;
		}
		if(0 == strncmp(msg.msg_data,"end",3))
		{
			printf("we finished to send data!\n") ;
			isRuning = false ;
		}
	}
	
	return 0 ;
	
}
