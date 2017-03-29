/*
 * $Revision: 1.00 $
 * $Author: Jiang xianxu $
 * $Date: 2017/03/01 $
 *                                                                       
 */
/** @file
 *
 *	This file defines the Mutex class.  This class defines
 *  the interface about Linux Mutex.
 */
/*
 ******************************************************************************
	Headers
 ******************************************************************************
 */
 #include "Mutex.h"
 
 /*
 ******************************************************************************
 *
 *  Mutex :: Mutex
 *
 ******************************************************************************
 */
 Mutex::Mutex(int mutextype)
 {
 	m_iLastError = 0 ;
 	pthread_mutexattr_t attr ;
 	
 	pthread_mutexattr_init(&attr) ;
	pthread_mutexattr_settype(&attr,mutextype) ;
	
	pthread_mutex_init(&m_mutex,&attr) ;
	pthread_mutexattr_destroy(&attr) ;
 }
 /*
 ******************************************************************************
 *
 *  Mutex :: ~Mutex
 *
 ******************************************************************************
 */
 Mutex::~Mutex()
 {
 	pthread_mutex_destroy(&m_mutex) ;
 }
 /*
 ******************************************************************************
 *
 *  Mutex :: Lock
 *
 ******************************************************************************
 */
 int Mutex::Lock()
 {
 	int RetVal = pthread_mutex_lock(&m_mutex) ;
 	if(RetVal < 0)
 	{
 		m_iLastError = RetVal ;
 		return PTHREAD_LOCK_FAILED ;
 	}
 }
 /*
 ******************************************************************************
 *
 *  Mutex :: Unlock
 *
 ******************************************************************************
 */
 int Mutex::Unlock()
 {
 	int RetVal = pthread_mutex_unlock(&m_mutex) ;
 	if(RetVal < 0)
 	{
 		m_iLastError = RetVal ;
 		return PTHREAD_UNLOCK_FAILED ;
 	}
 }
 /*
 ******************************************************************************
 *
 *  Mutex :: Trylock
 *
 ******************************************************************************
 */
 int Mutex::Trylock()
 {
 	int RetVal = pthread_mutex_trylock(&m_mutex) ;
 	if(RetVal < 0)
 	{
 		m_iLastError = RetVal ;
 		return PTHREAD_TRYLOCK_FAILED ;
 	}
 }
 /*
 ******************************************************************************
 *
 *  Mutex :: TimedLock
 *
 ******************************************************************************
 */
 int Mutex::TimedLock(const struct timespec* tsptr)
 {
 	int RetVal = pthread_mutex_timedlock(&m_mutex,tsptr) ;
 	if(RetVal < 0)
 	{
 		m_iLastError = RetVal ;
 		return PTHREAD_TIMEDLOCK_FAILED ;
 	}
 }
  /*
 ******************************************************************************
 *
 *  Mutex :: GetMutextTypeAttribute
 *
 ******************************************************************************
 */
int  GetMutextTypeAttribute()
{
	int mutextype = 0;
	pthread_mutexattr_t attr ;
 	
 	pthread_mutexattr_init(&attr) ;
	pthread_mutexattr_gettype(&attr,&mutextype) ;
	pthread_mutexattr_destroy(&attr) ;
	
	return mutextype ;
}
 /*
 ******************************************************************************
 *
 *  Mutex :: SetMutexTypeAttribute
 *
 ******************************************************************************
 */
void SetMutexTypeAttribute(int type)
{
	pthread_mutexattr_t attr ;
 	
 	pthread_mutexattr_init(&attr) ;
	pthread_mutexattr_settype(&attr,type) ;
	
	pthread_mutexattr_destroy(&attr) ;
}
 /*
 ******************************************************************************
 *
 *  Mutex :: SetProcessSharedAttribute
 *
 ******************************************************************************
 */
void SetProcessSharedAttribute(int pshared)
{
	pthread_mutexattr_t attr ;
 	
 	pthread_mutexattr_init(&attr) ;
	pthread_mutexattr_setpshared(&attr,pshared) ;
	
	pthread_mutexattr_destroy(&attr) ;
}
 /*
 ******************************************************************************
 *
 *  Mutex :: GetProcessSharedAttribute
 *
 ******************************************************************************
 */
int GetProcessSharedAttribute()
{
	int pshared = 0;
	pthread_mutexattr_t attr ;
 	
 	pthread_mutexattr_init(&attr) ;
	pthread_mutexattr_getpshared(&attr,&pshared) ;
	
	pthread_mutexattr_destroy(&attr) ;
	return pshared ;
}
 /*
 ******************************************************************************
 *
 *  Mutex :: SetRobustAttribute
 *
 ******************************************************************************
 */
void SetRobustAttribute(int robust)
{
	pthread_mutexattr_t attr ;
 	
 	pthread_mutexattr_init(&attr) ;
	pthread_mutexattr_setrobust(&attr,robust) ;

	pthread_mutexattr_destroy(&attr) ;
}
 /*
 ******************************************************************************
 *
 *  Mutex :: GetRobustAttribute
 *
 ******************************************************************************
 */
int GetRobustAttribute()
{
	int robust = 0;
	pthread_mutexattr_t attr ;
 	
 	pthread_mutexattr_init(&attr) ;
	pthread_mutexattr_getrobust(&attr,&robust) ;
	pthread_mutexattr_destroy(&attr) ;
}

