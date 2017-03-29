/*
 * $Revision: 1.00 $
 * $Author: Jiang xianxu $
 * $Date: 2017/03/01 $
 *                                                                       
 */
/** @file
 *
 *	This file defines the BaseThread class.  This virtual base class defines
 *  the interface for all worker threads.
 */
 
/*
 ******************************************************************************
	Switches
 ******************************************************************************
 */
#ifndef BASE_THREAD_H
#define BASE_THREAD_H

/*
 ******************************************************************************
	Header file
 ******************************************************************************
 */
#include <sys/types.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "errorCodes.h"
/*
 ******************************************************************************
	Macros
 ******************************************************************************
 */
#define DEFAULT_STACK_SIZE                1024*1024
#define INVALID_PTHREAD_KEY               0x10000l


/*
 ******************************************************************************
	Classes
 ******************************************************************************
 */
 
class BaseThread
{
public:
	//constructor and destructor function
	BaseThread() ;
	virtual ~BaseThread() ;
	//member function
	virtual int Initialize() ;
	/**
	****************************************************************************
	* In Run(), we set the thread attribute struct and create the thread.
	* Note: when we create thread,we must make 'this' as parameter of thread
	* function,bcause the thread funciton is static type,so it has no 'this'
	* pointer and can not access the non-static function and data of BaseThread.
	* and not polymorphic.
	****************************************************************************
	**/
	virtual int Run() ;
	/**
	****************************************************************************
	* The thread function,It need to be static function or friend function.
	* Note: it must not be member funciton because the member function has
	* 'this' pointer,it is not compatible with Linux thread,which declared
	* as void * (*func)(void *)
	****************************************************************************
	**/
	static void * ThreadFunction(void * pData);
	void ThreadMethod(void ) ;
	/**
	****************************************************************************
	* Execute() is the real thread function, every child class need to
	* overwirte this function to implement a personal thread.
	****************************************************************************
	**/
	virtual void Execute(void)=0 ;
	/**
	****************************************************************************
	* It is called in ThreadMothed() function before call Execute. it allows
	* child thread to do some personal work before enter real Execute function.
	****************************************************************************
	**/
	virtual void ThreadContextInit(void) ;
	/**
	****************************************************************************
	* It is called in ThreadMothed() function after call Execute. it allows
	* child thread to do some personal tail-in work after thread finished.
	****************************************************************************
	**/
	virtual void ThreadContextDestroy(void) ;
	/**
	****************************************************************************
	* This function will call pthread_join to wait thread shutdown if the 
	* thread is in joinable status. This function is invoked by main thread
	* which create the child thread.
	****************************************************************************
	**/
	virtual void WaitThreadToShutdown() ;
	/**
	****************************************************************************
	* This function aims to register a signal provide by signo that need to be
	* handled by thread.
	****************************************************************************
	*/
	int RegisterSignal(int signo) ;
	/**
	****************************************************************************
	* This function is the entry point when a signal occurs that is registered
	* by RegisterSignal() function, It will invoke the ThreadSignalHandler() 
	* to handle the signal.
	****************************************************************************
	*/
	static void SignalHandler(int Signo,siginfo_t * pSigInfo,void * pData) ;
	/**
	****************************************************************************
	* This function is used to handle a signal and It is a thread specific
	* function which means that any child thread need to overwrite it.
	****************************************************************************
	*/
	virtual int ThreadSignalHandler(int Signo) ;
	/**
	****************************************************************************
	* This function return the time as a number of milliseconds from Jan 1, 1970
	* It is a portal way to calcualting the elapsed time.
	****************************************************************************
	*/
	
	static unsigned long long GetTickCount() ;
	
	
	
	/**
	****************************************************************************
	* Set Functions
	****************************************************************************
	**/
	void SetDatached(bool bDatached) {m_bDetached = bDatached ;}
	void SetJoinable(bool bJoinable) {m_bJoinable = bJoinable ;}
	void SetStacksize(size_t stacksize) {m_stackSize = stacksize ;}
	/**
	****************************************************************************
	* Get Functions
	****************************************************************************
	**/
	bool GetDetached() {return m_bDetached ;}
	bool GetJoinable() {return m_bJoinable ;}
	bool GetStacksize() {return m_stackSize ;}
	bool IsThreadRuning() {return m_bRuningFlags;}
	pthread_t getChildThreadId(){return m_threadID ;}
		
private:
							  
	bool    m_bRuningFlags ;   /* flag to indicate if the thread is still runing.*/
							   	
							   									
	bool    m_bDetached ;      /* flag to indicate if the thread is in detached status*/
	
	bool    m_bJoinable ;      /* flags to indicate weather the thread is in joinable status */
	
	size_t  m_stackSize ;      /* the stack size of the thread */
	
	pthread_t m_threadID ;     /* the thread id */
};

#endif
