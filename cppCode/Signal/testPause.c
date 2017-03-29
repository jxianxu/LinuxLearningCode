#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <strings.h>

void sig_handler(int sigo)
{
	switch(sigo)
	{
	case SIGINT:
		printf("handle a signal SIGINT\n") ;
		exit(0) ;
		break ;
	case SIGALRM:
		printf("handle a signal SIGALRM\n") ;
		break ;
	case SIGQUIT:
		printf("handle a signal SIGQUIT\n") ;
		exit(0) ;
		break ;
	}

}
void sighandler(int signo, siginfo_t* info, void * ctx)
{
	printf("Receive a signal: sigint: %d\n",info->si_int) ;
	printf("Data from sigqueue: %d",info->si_value.sival_int) ;
}

int main()
{
	return 0;
}

