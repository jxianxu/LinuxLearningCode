/*
 * $Revision: 1.00 $
 * $Author: Jiang xianxu $
 * $Date: 2017/03/02 $
 *                                                                       
 */
/** @file
 *
 *	This file defines the TimerManager class.  This class defines
 *  the interface for Timer Management.
 */
 
 /*
 ******************************************************************************
	Header file
 ******************************************************************************
 */
#include "TimerManager.h"

/*
 ******************************************************************************
	Variables
 ******************************************************************************
 */
 
TimerManager * TimerManager::m_pTimerManager = NULL; 	
Mutex          TimerManager::m_sInstanceMutex(PTHREAD_MUTEX_RECURSIVE_NP); 
int            TimerManager::m_sRefCount = 0;

TimerNode::TimerNode()
{
	memset(this,0,sizeof(TimerNode)) ;
	m_offset = TIMER_DISABLED ;
}
TimerNode::TimerNode(const TimerNode& node)
{
	memcpy(this,&node,sizeof(TimerNode)) ;
}
void TimerNode::operator=(const TimerNode& node)
{
	memcpy(this,&node,sizeof(TimerNode)) ;
}

TimerManager::TimerManager():BaseThread(),m_TimerListMutex(),m_bDone(false),m_iNextTimerId(1){} ;

TimerManager::~TimerManager()
{
	if(!m_bDone)
	{
		StartShutDown() ;
	}
	WaitThreadToShutdown() ;
}
int TimerManager::Initialize()
{
	int RetVal = 0;
	RetVal = BaseThread::Initialize() ;
	if(RetVal != SUCCESS_OK)
	{
		return TIMER_MANAGER_INITIAL_ERROR ;
	}
	
	RetVal = Run() ;
	if(RetVal < 0)
	{
		return TIMER_MANAGER_RUN_FAILED ;
	}
	
	RetVal = RegisterSignal(SIGUSR1) ;
	if(RetVal < 0)
	{
		return TIMER_REGISTER_FAILED ;
	}
	return SUCCESS_OK ;
	
}
void TimerManager::Release()
{
	m_sInstanceMutex.Lock() ;
	if(m_pTimerManager != NULL)
	{
		if(--m_sRefCount == 0)
		{
			delete m_pTimerManager ;
			m_pTimerManager = NULL ;
		}
	}
	
	m_sInstanceMutex.Unlock() ;
}
TimerManager * TimerManager::Create()
{
	m_sInstanceMutex.Lock() ;
	int RetVal = 0 ;
	TimerManager * pInstance = NULL ;
	if(NULL == m_pTimerManager)
		m_pTimerManager = new TimerManager() ;
	else
		m_sRefCount++ ;
	RetVal = m_pTimerManager->Initialize() ;
	if(RetVal < 0)
	{
		delete m_pTimerManager ;
		m_pTimerManager = NULL ;
		m_sInstanceMutex.Unlock() ;
		return NULL ;
	}
	pInstance = m_pTimerManager ;
	m_sRefCount ++ ;
	m_sInstanceMutex.Unlock() ;
	return pInstance ;
}
void TimerManager::Execute(void)
{
	fd_set readset ;
	fd_set writeset ;
	fd_set errorset ;
	struct timeval val ;
	while(!m_bDone)
	{
		FD_ZERO(&readset);
		FD_ZERO(&writeset);
		FD_ZERO(&errorset);
		
		unsigned long duration = processTimerEvent() ;
		
		if(duration > 0)
		{
			val.tv_sec = duration/1000ul ;
			val.tv_usec = (duration % 1000ul)*1000ul ;
			
		}
		if(m_bDone)
			break ;
		select(0,&readset,&writeset,&errorset,(duration > 0)? &val : NULL) ;
		
	}
}
void TimerManager::StartShutDown()
{
	//if(IsRuning())
		m_bDone = true ;
}
unsigned long TimerManager::CreateTimer(TimerEventHandler * pHandler)
{
	TimerNode timer ;
	timer.m_timerId = m_iNextTimerId ++ ;
	timer.pHandler = pHandler ;
	
	m_TimerListMutex.Lock() ;
	
	m_timerList.insert(std::make_pair(timer.m_timerId,timer)) ;
	
	m_TimerListMutex.Unlock() ;
	
	return timer.m_timerId ;
}
int TimerManager::SetTimer(unsigned long timerId,unsigned long offset,unsigned long period)
{
	TimerListMap::iterator matchid ;
	matchid = m_timerList.find(timerId) ;
	m_TimerListMutex.Lock() ;
	if(matchid != m_timerList.end() )
	{
		TimerNode& timer = matchid->second ;
		timer.m_offset = offset ;
		timer.m_period = period ;
		timer.m_setTime = BaseThread::GetTickCount() ;
		timer.m_LastFireTime = 0 ;
		m_TimerListMutex.Unlock() ;
		return SUCCESS_OK ;
	}
	m_TimerListMutex.Unlock() ;
	return TIMER_NOT_FOUND ;
}
int TimerManager::CancelTimer(unsigned long timerId)
{
	int RetVal = SetTimer(timerId,TIMER_DISABLED,0);
	return RetVal ;
}
int TimerManager::DestroyTimer(unsigned long timerId)
{
	TimerListMap::iterator iter ;
	m_TimerListMutex.Lock() ;
	iter = m_timerList.find(timerId);
	if(iter != m_timerList.end())
	{
		m_timerList.erase(iter) ;
		m_TimerListMutex.Unlock() ;
		return SUCCESS_OK ;
	}
	m_TimerListMutex.Unlock() ;
	return TIMER_NOT_FOUND ;
}
unsigned long TimerManager::processTimerEvent()
{
	TimerListMap::iterator iter ;
	unsigned long duration = 0;
	unsigned long long nextTime = 0 ;
	m_TimerListMutex.Lock() ;
	for(iter = m_timerList.begin() ; iter != m_timerList.end() ; iter ++)
	{
		TimerNode& timer = iter->second ;
		if(timer.m_offset == TIMER_DISABLED)
			continue ;
		unsigned long long currentTime = BaseThread::GetTickCount() ;
		unsigned long long baseTime = timer.m_setTime + timer.m_offset ;
		if(baseTime <= currentTime)
		{
			timer.pHandler->DoTimerEvent(timer.m_timerId) ;
			timer.m_LastFireTime = currentTime ;
		}
			
		
		if(0 == timer.m_LastFireTime)
		{
			nextTime = baseTime ;
		}
		else if(timer.m_period > 0)
		{
			nextTime = baseTime+((currentTime - timer.m_setTime + timer.m_offset)/timer.m_period)*timer.m_period ;
		}
		else
		{
			timer.m_offset = TIMER_DISABLED ;
			continue ;
		}
		unsigned long Diff = 10 ;
		if(nextTime > currentTime)
			Diff = nextTime - currentTime ;
		if(0 == duration || Diff < duration)
			duration = Diff ;
		
	}
	m_TimerListMutex.Unlock() ;
	return duration ;
}

  

