#include <iostream>
#include "EventLoopThread.h"

using namespace std ;

int main()
{
	EventLoopThread thread(3000,2000) ;
	thread.Initialize() ;
	thread.Run() ;
	
	thread.WaitThreadToShutdown() ;
		
	return 0 ;
}
