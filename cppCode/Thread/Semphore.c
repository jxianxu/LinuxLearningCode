#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
//#include <sys/sem.h>
#include <linux/sem.h>
#include <stdbool.h>

int CreateSemphore(key_t key,int num_sems,int sem_flags);
int Initialize(int sem_id,int num_sems,int command) ;
int Destroy(int sem_id) ;

int P_Operator(int sem_id) ;
int V_Operator(int sem_id) ;

int main()
{
	int i = 0 ; 
	int sem_id = 0 ;
	// 1. create a semphore
	if((sem_id = CreateSemphore((key_t)123,1,0666|IPC_CREAT)) < 0)
	{
		printf("Create Semphore failed!\n") ;
		exit(0) ;
	}
	// 2. Initialize a semphore
	if(Initialize(sem_id,0,SETVAL) < 0)
	{
		printf("Initialize semphore failed!\n") ;
		exit(0) ;	
	}
	// 3. use a semphoer in a for loop
	for(i = 0 ; i < 10 ; i++)
	{
		// Enter critical section
		if(P_Operator(sem_id) < 0)
		{
			printf("P Operator failed!\n") ;
			break ;
		}
		// do some work
		printf("I have enter the critical section for %d times.\n",i+1) ;

		// Leave critical section
		if(V_Operator(sem_id) < 0)
		{
			printf("V Operation failed!\n") ;
			break ;
		}
		sleep(2) ;
	}
	Destroy(sem_id) ;
	return 0 ;
}
int CreateSemphore(key_t key,int num_sems,int sem_flags)
{
	int sem_id = semget(key,num_sems,sem_flags) ;
	return sem_id ;
}
int Initialize(int sem_id,int num_sems,int command)
{
	union semun sem_union ;
	sem_union.val = 1 ;
	return semctl(sem_id,num_sems,command,sem_union) ;
}
int Destroy(int sem_id)
{
	return semctl(sem_id,0,IPC_RMID) ;
}
int P_Operator(int sem_id)
{
	struct sembuf sem_buf ;
	sem_buf.sem_num = 0 ;
	sem_buf.sem_op = -1 ;
	sem_buf.sem_flg  = SEM_UNDO ;
	return semop(sem_id,&sem_buf,1) ;
}
int V_Operator(int sem_id)
{
	struct sembuf sem_buf ;
	sem_buf.sem_num = 0 ;
	sem_buf.sem_op = 1 ;
	sem_buf.sem_flg  = SEM_UNDO ;
	return semop(sem_id,&sem_buf,1) ;
}

