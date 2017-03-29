#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

void travleFileOFDir(const char * path) ;
int main()
{
	travleFileOFDir("/home/jiang/src/cppCode") ;
	return 0 ;
}
void travleFileOFDir(const char * path)
{
	struct dirent* entry ;
	DIR * dir = NULL ;
	dir = opendir(path) ;
	
	while(NULL != (entry = readdir(dir)))
	{
		printf("file name: %s\n",entry->d_name) ;
	}
	if(!entry)
	{
		printf("readdir failed!\n") ;
		exit(0) ;
	}
	closedir(dir) ;
}
