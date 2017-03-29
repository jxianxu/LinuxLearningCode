/*
 * $Revision: 1.00 $
 * $Author: Jiang xianxu $
 * $Date: 2017/03/03 $
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
	Switches
 ******************************************************************************
 */
 
 #ifndef EVENT_LOOP_THREAD_H
 #define EVENT_LOOP_THREAD_H
 
 /*
 ******************************************************************************
	Header files
 ******************************************************************************
 */
 
 #include "BaseThread.h"
 #include "TimerManager.h"
 #include "NotifyEvent.h"
 #include "PriorityQueue.h"
 #include "common.h"
 /*
 ******************************************************************************
	Macros 
 ******************************************************************************
 */
 
 /*
 ******************************************************************************
	classes 
 ******************************************************************************
 */
 
 class EventLoopThread : public BaseThread, public TimerEventHandler
 {
 public:
 	EventLoopThread(int period=0,int offset= 0):m_pTimerMgr(NULL),m_bDone(false),m_iOffset(offset),m_iTimerPeriod(period),m_iTimerId(0)
 	{
 	}
 	~EventLoopThread() ;
 	
 	 /*
 	******************************************************************************
	* Do all the initialization before thread method is invoked such as create
	* a instance of TimerManager, set the maxmum depth of priority queue, and
	* create a waitable timer and so on.
 	******************************************************************************
 	*/
 	virtual int Initialize() ;
 	
 	/*
 	******************************************************************************
	* The actul thread method. It runing a while loop in which waiting messages 
	* using WaitForMessage() and then handling coming messages using 
	* ProcessThreadMessage()  
 	******************************************************************************
 	*/
 	
 	virtual void Execute() ;
 	
 	/*
 	******************************************************************************
	* The actual timer event handler, it will post a timer event to thread using
	* ProcessThreadMessage().
 	******************************************************************************
 	*/
 	
 	virtual void DoTimerEvent(unsigned long timerId) ;
 	
 	/*
 	******************************************************************************
	* Create a timer and make this class as the timer event handler class.
 	******************************************************************************
 	*/
 	
 	unsigned long CreateWaitableTimer( ) ;
 	
 	/*
 	******************************************************************************
	* Set the timer information such as  period, offset 
 	******************************************************************************
 	*/
 	
 	int SetWaitableTimer( ) ;
 	
 	/*
 	******************************************************************************
	* Cancel the timer given by parameter timerId
 	******************************************************************************
 	*/
 	
 	int CancelWaitableTimer( unsigned long timerId ) ;
 	
 	/*
 	******************************************************************************
	* Destroy the timer given by parameter timerId
 	******************************************************************************
 	*/
 	
 	int DestroyWaitableTimer( unsigned long timerId ) ;
 	
 	
 	
 	virtual unsigned long processTimerEvent(unsigned long timerId) ;
 	
 	/*
 	******************************************************************************
	* when a thread message is coming. call this function to handle the message.
 	******************************************************************************
 	*/
 	
 	virtual void ProcessThreadMessage( unsigned long message,unsigned long wParam,unsigned long lParam ) ;
 	
 	/*
 	******************************************************************************
	* this function will blocked until a message arrived to priority queue. 
 	******************************************************************************
 	*/
 	
 	int WaitForMessage( unsigned long duation,MessageNode& node) ;
 	
 	/*
 	******************************************************************************
	* set the maxmum depth of message queue. 
 	******************************************************************************
 	*/
 	
 	void SetQueueMaxDepth( size_t maxDepth) ;
 	
 	int ResetTimerPeriod( unsigned long newPeriod ) ;
 	
 	void PostThreadMessage(unsigned long message, unsigned long wParam, unsigned long lParam,int pri=PRIORITY_LOW) ;
 	
 	virtual void StartShutDown(void) ;
 	
 	virtual void ThreadContextDestroy(void) ;
 	virtual void CleanupThreadMessage(unsigned long message, unsigned long wParam, unsigned long lParam) ;
 	bool IsRuning() {return m_bDone ;};
 private:
 	PriorityQueue             m_MessageQueue ;
 	
 	TimerManager *            m_pTimerMgr ;
 	
 	bool                      m_bDone ;
 	
 	unsigned long             m_iTimerPeriod ;
 	
 	unsigned long             m_iTimerId ;
 	
 	unsigned long             m_iOffset ;
 	
 	NotifyEvent               m_event ;
 };
 
 #endif
