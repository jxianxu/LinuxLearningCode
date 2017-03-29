#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int pid = 0 ;
	int status = 0 ;
	if(-1 == (pid = fork()))
	{
		printf("fork error!\n") ;
		exit(0) ;
	}
	
	if(0 == pid)
	{
		// child process
		printf("I am child,my pid is : %d,my parent pid is : %d\n",getpid(),getppid()) ;
		sleep(3) ;
		exit(0) ;
	}
	else
	{
		// parent process
		printf("I am parent,my pid is : %d, my child pid is : %d\n",getpid(),pid) ;
		int pid_term = wait(&status) ;
		if(WIFEXITED(status))
			printf("the pid %d is normal terminated! and the return value is %d\n",pid_term,WEXITSTATUS(status)) ;
	}
	return 0 ;
	
}
