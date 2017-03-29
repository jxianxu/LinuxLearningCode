/*
 * $Revision: 1.00 $
 * $Author: Jiang xianxu $
 * $Date: 2017/03/04 $
 *                                                                       
 */
/** @file
 *
 *	This file defines the EventLoopThread class.  This class defines
 *  the interface about EventLoop base worker thread. It can be used
 *  by those threads who need process message. It also provide a
 *  built-in periodic timer. 
 */
 
 /*
 ******************************************************************************
	Header files
 ******************************************************************************
 */
 
 #include "EventLoopThread.h"
 EventLoopThread::~EventLoopThread()
 {
 		if(IsRuning())
 		{
 			StartShutDown() ;
 			WaitThreadToShutdown() ;
 		}
 		if(m_pTimerMgr != NULL)
 		{
 			if(0 == m_iTimerId)
 			{
 				m_pTimerMgr->DestroyTimer(m_iTimerId) ;
 				m_iTimerId = 0 ;
 				m_pTimerMgr->Release() ;
 			}
 			
 		}	
 }
 int EventLoopThread::Initialize()
 {
 	
 	if(m_iTimerPeriod != 0)
 	{
 		m_pTimerMgr = TimerManager::Create() ;
 		if(NULL == m_pTimerMgr)
 			return EVENTLOOP_THREAD_TIMERMGR_NULL ;
 		m_iTimerId = CreateWaitableTimer() ;
 		int ret =  SetWaitableTimer() ;
 		if(ret < 0)
 			return ret ;
 	}	
 	return BaseThread::Initialize() ;
 }
 
 void EventLoopThread::Execute()
 {
 	while(!m_bDone)
 	{
 		struct MessageNode msg ;
 		int ret = WaitForMessage(NOTIFY_EVENT_WAIT_INFINITE,msg) ;
 		if(m_bDone || (ret == SUCCESS_OK && msg.message == MSG_SHUTDOWN ))
 		{
 			break ;
 		}
 		
 		if(ret == SUCCESS_OK)
 		{
 			if(msg.message == MSG_TIMER_EVENT)
 			{
 				processTimerEvent(m_iTimerId) ;
 			}	
 			else if(msg.message == MSG_THREAD_MSG)
 			{	
 				ProcessThreadMessage(msg.message,msg.wParam,msg.lParam) ;
 			}
 		}
 	}
 }
 
 void EventLoopThread::DoTimerEvent(unsigned long timerId)
 {
 	PostThreadMessage(MSG_TIMER_EVENT,timerId,0) ;
 }
 void EventLoopThread::PostThreadMessage(unsigned long message, unsigned long wParam, unsigned long lParam,int priority)
 {
 	m_MessageQueue.Push(message,wParam,lParam,priority) ;
 	m_event.Notify() ;
 }
 unsigned long EventLoopThread::CreateWaitableTimer() 
 {
 	if( m_pTimerMgr == NULL)
 	{
 		return 0 ;
 	}
 	return m_pTimerMgr->CreateTimer(this) ;
 }
 int EventLoopThread::SetWaitableTimer( ) 
 {
 	if( m_pTimerMgr == NULL)
 	{
 		return EVENTLOOP_THREAD_TIMERMGR_NULL ;
 	}
 	return m_pTimerMgr->SetTimer(m_iTimerId,m_iOffset,m_iTimerPeriod) ;
 }
 int EventLoopThread::CancelWaitableTimer( unsigned long timerId )
 {
 	if( m_pTimerMgr == NULL)
 	{
 		return EVENTLOOP_THREAD_TIMERMGR_NULL ;
 	}
 	return m_pTimerMgr->CancelTimer(m_iTimerId) ;
 }
 int EventLoopThread::DestroyWaitableTimer( unsigned long timerId )
 {
 	if( m_pTimerMgr == NULL)
 	{
 		return EVENTLOOP_THREAD_TIMERMGR_NULL ;
 	}
 	m_pTimerMgr->DestroyTimer(m_iTimerId) ;
 }
 
 unsigned long EventLoopThread::processTimerEvent(unsigned long timerId) 
 {
 	printf("Receive a timer event!\n") ;
 }
 void EventLoopThread::ProcessThreadMessage( unsigned long message,unsigned long wParam,unsigned long lParam )
 {
 	printf("receive thread message!\n") ;
 }
 int EventLoopThread::WaitForMessage( unsigned long duation,MessageNode& node)
 {
 	int ret = m_event.WaitNotify(duation) ;
 	if(ret == SUCCESS_OK)
 	{
 		return m_MessageQueue.Pop(node) ;
 	}
 	return ret ;
 }
 void EventLoopThread::SetQueueMaxDepth( size_t maxDepth) 
 {
 	m_MessageQueue.SetMaxQueueDepth((int)maxDepth) ;
 }
int EventLoopThread::ResetTimerPeriod( unsigned long newPeriod )
{
	if( m_pTimerMgr == NULL)
 	{
 		return EVENTLOOP_THREAD_TIMERMGR_NULL ;
 	}
 	m_iTimerPeriod = newPeriod ;
 	return m_pTimerMgr->SetTimer(m_iTimerId,m_iOffset,newPeriod) ;
}
void EventLoopThread::StartShutDown(void)
{
	m_bDone = false ;
	PostThreadMessage(MSG_SHUTDOWN,0,0) ;
}
void EventLoopThread::ThreadContextDestroy(void)
{
	struct MessageNode node ;
	while(m_MessageQueue.Pop(node) == SUCCESS_OK)
	{
		if(node.message != MSG_SHUTDOWN && (node.message != MSG_TIMER_EVENT))
		{
			CleanupThreadMessage(node.message,node.wParam,node.lParam) ;
		}
	}
}
void EventLoopThread::CleanupThreadMessage(unsigned long message, unsigned long wParam, unsigned long lParam)
{

}
