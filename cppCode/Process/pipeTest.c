#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int pid = 0 ;
	int status = 0 ;
	int fd[2] ;
	if(pipe(fd)< 0)
	{
		printf("pipe error!\n") ;
	}
	if(-1 == (pid = fork()))
	{
		printf("fork error!\n") ;
		exit(0) ;
	}
	
	if(0 == pid)
	{
		// child process
		char buf[64] ;
		close(fd[1]) ;
		int n = read(fd[0],buf,64) ;
		buf[n] = '\0' ;
		printf("child read data from parent: %s\n",buf) ;
	}
	else
	{
		// parent process
		close(fd[0]) ;
		write(fd[1],"Hi, I am your parent,I am sending data to you!\n",48) ;	
	}
	return 0 ;
	
}
