#include <iostream>
#include "Mutex.h"

using namespace std ;

int main()
{
	int data ,i =  0;
	Mutex mutex ;
	mutex.Lock() ;
	for(i = 0 ;i < 10 ; i++)
	{
		data ++ ;
	}
	mutex.Unlock() ;
	cout<<"data"<<data<<endl ;
	return 0 ;
}
