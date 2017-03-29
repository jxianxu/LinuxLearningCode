#ifndef CHILD_THREAD_H
#define CHILD_THREAD_H

#include "BaseThread.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
class ChildThread : public BaseThread
{
public:
	ChildThread() {data = 0 ;};
	virtual ~ChildThread(){} ;
	virtual void Execute(void) ;
	
	virtual void ThreadContextInit(void) ;
	virtual void ThreadContextDestroy(void) ;
	virtual void Display();
public:
	int data ;
	
};

#endif
