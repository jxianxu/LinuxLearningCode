#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
	struct stat filestat ;
	int ret = stat("/home/jiang/src/cppCode/ConditionalVar.c",&filestat) ;
	if(ret < 0)
	{
		printf("get file metadata failed!\n") ;
		exit(0) ;
	}
	printf("File MetaData as following:\n") ;
	
	printf("ID of device containing this file: %d\n",filestat.st_dev) ;
	printf("inode number: %d\n",filestat.st_ino) ;
	printf("permission : %d\n",filestat.st_mode) ;
	printf("number of hard links: %d\n",filestat.st_nlink) ;
	printf("Uid of this file: %d\n",filestat.st_uid) ;
	printf("Gid of this file: %d\n",filestat.st_gid) ;
	printf("Total size in bytes: %d\n",filestat.st_size) ;
	printf("blocksize for filesystem IO: %d\n",filestat.st_blksize) ;
	printf("number of blocks: %d\n",filestat.st_blocks) ;
	
	return 0 ;	
}
