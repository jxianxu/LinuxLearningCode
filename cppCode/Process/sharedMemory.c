#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/shm.h>

struct Content
{
	char content[128] ;
};

int CreateSharedMemory(key_t key,size_t size, int shflgs) ;
void * GetSharedMemory(int shm_id,const void * shm_addr,int shmflgs) ;
int DetachSharedMemory(void * shmaddr) ;
int DeleteSharedMemory(int shm_id,int command) ;
int main()
{
	int shm_id = 0 ;
	struct Content* pData = NULL;
	//1. create shared memory
	shm_id = CreateSharedMemory((key_t)123,sizeof(struct Content),0666|IPC_CREAT) ;
	if(-1 == shm_id)
	{
		printf("Create shared memory failed!\n") ;
		exit(0) ;
	}
	//2. Get shared memory just created!
	pData = (struct Content *)GetSharedMemory(shm_id,NULL,0) ;
	if(NULL == pData)
	{
		printf("Get shared memory failed!\n") ;
		exit(0) ;
	}
	//3. Do something in shared memory. (Read or Write)
	strcpy(pData->content,"Hello I am writing data to shared memory!") ;
	printf("Read data from shared memory: %s\n",pData->content) ;
	
	//4. Detach Shared memory
	if(DetachSharedMemory(pData)< 0)
	{
		printf("Detach shared memory failed!\n") ;
		exit(0) ;
	}
	// delete shared memory
	if( DeleteSharedMemory(shm_id,IPC_RMID)< 0)
	{
		printf("delete shared memory failed!\n") ;
		exit(0) ;
	}
	
	return 0 ;
}

int CreateSharedMemory(key_t key,size_t size, int shflgs)
{
	return shmget(key,size,shflgs) ;
}
void * GetSharedMemory(int shm_id,const void * shm_addr,int shmflgs)
{
	return shmat(shm_id,shm_addr,shmflgs) ;
}

int DetachSharedMemory(void * shmaddr)
{
	return shmdt(shmaddr) ;
}
int DeleteSharedMemory(int shm_id,int command)
{
	return shmctl(shm_id,IPC_RMID,0) ;
}
