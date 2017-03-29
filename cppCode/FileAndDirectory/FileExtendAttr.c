#include <sys/types.h>
#include <sys/xattr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void SetExtendAttr() ;
void ListExtendAttr() ;

int main()
{
	//SetExtendAttr() ;
	ListExtendAttr() ;
	return 0 ;
}
void SetExtendAttr()
{
	
	char *filename = "/home/jiang/src/cppCode/testPause.c" ;
	int ret = setxattr(filename,"user.jiang","12345",strlen("12345"),0) ;
	if(-1 == ret)
	{
		printf("set key-value:user.jiang failed!\n") ;
		exit(0) ;
	}
	ret = setxattr(filename,"user.xian","xxxxxx",strlen("xxxxxx"),0) ;
	if(-1 == ret)
	{
		printf("set key-value:user.xian failed!\n") ;
		exit(0) ;
	}
	ret = setxattr(filename,"user.xu","uuuuu",strlen("uuuuu"),0) ;
	if(-1 == ret)
	{
		printf("set key-value:user.xu failed!\n") ;
		exit(0) ;
	}
}
void ListExtendAttr()
{
	char * buf,*key,*value ;
	int buflen,keylen,valuelen ;
	char *filename = "/home/jiang/src/cppCode/testPause.c" ;
	
	//firstly, get the attr key length
	buflen = listxattr(filename,NULL,0) ;
	if(buflen == -1)
	{
		printf("get key len failed!\n") ;
		exit(0) ;
	}
	else if(buflen == 0)
	{
		printf("there is no extend attributes in the given file!\n") ;
		exit(0) ;
	}
	//allocate memory for buf of key
	buf = (char *)malloc(buflen) ;
	if(NULL == buf)
	{
		printf("allocate memory for key buf failed!\n") ;
		exit(0) ;
	}

	
	
	//copy the list of extend attribute keys of the given file.
	buflen = listxattr(filename,buf,buflen) ;
	if(-1 == buflen)
	{
		printf("copy the list of extend attrbute keys falied\n") ;
		exit(0) ;
	}
	
	key = buf ;
	while(buflen > 0) //get the attribute value by loop
	{
		printf("key: %s : ",key) ;
		//Determine length of the value.
		valuelen = getxattr(filename,key,NULL,0) ;
		if(-1 == valuelen)
		{
			printf("get length of the value failed!\n") ;
			exit(0) ;
		}
		if(valuelen > 0)
		{
			//allocate memory for value
			value = (char *)malloc(valuelen+1) ;
			if(NULL == value )
			{
				printf("allocate value memory failed!\n") ;
				exit(0) ;
			}
			valuelen = getxattr(filename,key,value,valuelen) ;
			if(valuelen == -1)
			{
				printf("get value failed!\n") ;
				exit(0) ;
			}	
			value[valuelen] = 0 ;
			printf("%s\n",value) ;
			free(value) ;
		}
		else
		{
			printf("<No Value>\n") ;
		}
		keylen = strlen(key)+1 ;
		buflen -= keylen ;
		key += keylen ;
	}
	free(buf) ;
	
}
