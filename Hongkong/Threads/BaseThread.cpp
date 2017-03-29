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
	Headers
 ******************************************************************************
 */
#include "BaseThread.h"

/*
 ******************************************************************************
	Variables
 ******************************************************************************
 */
static pthread_key_t s_thread_key = INVALID_PTHREAD_KEY;

/*
 ******************************************************************************
 *
 *  BaseThread :: BaseThread
 *
 ******************************************************************************
 */
BaseThread::BaseThread():m_bRuningFlags(false),m_bDetached(false),m_stackSize(DEFAULT_STACK_SIZE),m_threadID(0),m_bJoinable(false)
{
	if(INVALID_PTHREAD_KEY == s_thread_key)
		pthread_key_create(&s_thread_key,NULL) ;
}
/*
 ******************************************************************************
 *
 *  BaseThread :: ~BaseThread
 *
 ******************************************************************************
 */
BaseThread::~BaseThread()
{
	
}
/*
 ******************************************************************************
 *
 *  BaseThread :: Initialize
 *
 ******************************************************************************
 */
int BaseThread::Initialize()
{
	return SUCCESS_OK ;	
}
/*
 ******************************************************************************
 *
 *  BaseThread :: Run
 *
 ******************************************************************************
 */
int BaseThread::Run()
{
	pthread_attr_t attr ;
	if(m_bRuningFlags)
		return SUCCESS_OK ;
	int ret = pthread_attr_init(&attr) ;
	if(ret < 0)
	{
		return PTHREAD_ATTR_INIT_ERROR ;
	}
	
	ret = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE) ;
	if(ret < 0)
	{
		return PTHREAD_SET_DETACHED_ERROR ;
	}
	
	ret = pthread_attr_setstacksize(&attr,m_stackSize) ;
	if(ret < 0)
	{
		return PTHREAD_SET_STACKSIZE_ERROR ;
	}
	
	m_bRuningFlags = true ;
	m_bJoinable = true ;
	
	ret = pthread_create(&m_threadID,&attr,ThreadFunction,this) ;
	if(ret < 0)
	{
		m_bRuningFlags = false ;
		m_bJoinable = false ;
		
	}
	pthread_attr_destroy(&attr) ;
	return SUCCESS_OK ;
}
/*
 ******************************************************************************
 *
 *  BaseThread :: ThreadFunction
 *
 ******************************************************************************
 */
void * BaseThread::ThreadFunction(void * pData)
{
	
	BaseThread * pMyThread = (BaseThread *)pData ;
	if(INVALID_PTHREAD_KEY != s_thread_key)
	{
		pthread_setspecific(s_thread_key,pData) ;
	}
	
	pMyThread->ThreadMethod() ;
	
	if(INVALID_PTHREAD_KEY != s_thread_key)
	{
		pthread_setspecific(s_thread_key,NULL) ;
	}
	pMyThread->m_bRuningFlags = false ;
}
/*
 ******************************************************************************
 *
 *  BaseThread :: ThreadMethod
 *
 ******************************************************************************
 */
void BaseThread::ThreadMethod(void )
{
	
	ThreadContextInit() ;
	Execute() ;
	ThreadContextDestroy() ;
}
/*
 ******************************************************************************
 *
 *  BaseThread :: ThreadContextInit
 *
 ******************************************************************************
 */
void BaseThread::ThreadContextInit(void)
{

}
/*
 ******************************************************************************
 *
 *  BaseThread :: ThreadContextDestroy
 *
 ******************************************************************************
 */
void BaseThread::ThreadContextDestroy(void)
{

}
/*
 ******************************************************************************
 *
 *  BaseThread :: WaitThreadToShutdown
 *
 ******************************************************************************
 */
void BaseThread::WaitThreadToShutdown()
{
	if(!m_bDetached && m_bJoinable)
	{
		pthread_join(m_threadID,NULL) ;
		m_bJoinable = false ;
		m_threadID = false ;
	}
}
/*
 ******************************************************************************
 *
 *  BaseThread :: RegisterSignal
 *
 ******************************************************************************
 */
int BaseThread::RegisterSignal(int signo)
{
	int RetVal = 0 ;
	struct sigaction action ;
	action.sa_sigaction = SignalHandler ;
	action.sa_flags = SA_SIGINFO ;
	RetVal = sigaction(signo,&action,NULL) ;
	if(RetVal < 0)
		return PTHREAD_SIGACTION_ERROR ;
	return SUCCESS_OK ;
}
/*
 ******************************************************************************
 *
 *  BaseThread :: SignalHandler
 *
 ******************************************************************************
 */
void BaseThread::SignalHandler(int Signo,siginfo_t * pSigInfo,void * pData)
{
	BaseThread * pThread = NULL ;
	if(s_thread_key != INVALID_PTHREAD_KEY)
	{
		pThread = (BaseThread *)pthread_getspecific(s_thread_key) ;
	}
	if(NULL != pThread)
	{
		pThread->ThreadSignalHandler(Signo) ;
	}
}
/*
 ******************************************************************************
 *
 *  BaseThread :: ThreadSignalHandler
 *
 ******************************************************************************
 */
int BaseThread::ThreadSignalHandler(int Signo)
{
	// BaseThread simply return OK
	return SUCCESS_OK ;
}
/*
 ******************************************************************************
 *
 *  BaseThread :: GetTickCount
 *
 ******************************************************************************
 */
unsigned long long BaseThread::GetTickCount()
{
	unsigned long long tickCount = 1;
	struct timespec currentTime ;
	clock_gettime(CLOCK_REALTIME,&currentTime) ;
	tickCount = currentTime.tv_sec ;
	tickCount *= 1000ul ;
	tickCount += (currentTime.tv_nsec/1000000ul) ;
	return tickCount ;
}
