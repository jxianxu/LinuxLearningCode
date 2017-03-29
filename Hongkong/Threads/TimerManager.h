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
	Switches
 ******************************************************************************
 */
 #ifndef TIMER_MANAGER_H
 #define TIMER_MANAGER_H
 
/*
 ******************************************************************************
	Header file
 ******************************************************************************
 */
 #include "BaseThread.h"
 #include "Mutex.h"
 #include <string.h>

 #include <map>
 #include <unistd.h>
 /*
 ******************************************************************************
	Forward References
 ******************************************************************************
 */
  class TimerEventHandler ;
 /*
 ******************************************************************************
	Macros
 ******************************************************************************
 */
 
 #define TIMER_DISABLED                     0xFFFFFFFFul


 /*
 ******************************************************************************
	Structs definitions
 ******************************************************************************
 */

 struct TimerNode
 {
 	TimerNode() ;
 	TimerNode(const TimerNode& node) ;
 	
 	void operator=(const TimerNode& node) ;
 	unsigned long m_timerId ;
 	unsigned long long m_setTime ;
 	unsigned long long m_LastFireTime ;
 	unsigned long m_offset ;
 	unsigned long m_period ;
 	TimerEventHandler * pHandler ;
 	
 };
 /*
 ******************************************************************************
	Type definitions
 ******************************************************************************
 */
 
 typedef std::map<unsigned long,TimerNode> TimerListMap ;
 
 /*
 ******************************************************************************
	Classes
 ******************************************************************************
 */
 class TimerEventHandler
 {
 public:
 	TimerEventHandler(){} ;
 	virtual void DoTimerEvent(unsigned long timerId)=0 ;
 };
 
 class TimerManager : public BaseThread
 {
 private:
	/**
	****************************************************************************
	* Constructor. Notice that it is private,because the TimerManager is
	* Singleton.
	****************************************************************************
	**/
 	TimerManager() ;
 	
 public:
 	/**
	****************************************************************************
	* Destructor. 
	****************************************************************************
	**/
 	~TimerManager() ;
 	/**
	****************************************************************************
	* Initialize the TimerManager.
	* 1. call BaseThread's Constructor.
	* 2. call Run to create a thread.
	* 3. Create Signal handler to handle SIGUSR1
	****************************************************************************
	**/
 	virtual int Initialize() ;
 	
 	/**
	****************************************************************************
	* Release the TimerManager instance. decrease reference count value,if
	* the value is decreased to 0,delete the timerManager. 
	****************************************************************************
	**/
	
 	void Release() ;
 	
 	/**
	****************************************************************************
	* Return a Singleton instance of TimerManager. 
	****************************************************************************
	**/
	
 	static TimerManager * Create() ;
 	/**
	****************************************************************************
	* The actul thread function. it process timer events repeatly in a while
	* loop. 
	****************************************************************************
	**/
 	virtual void Execute(void) ;
 	
 	/**
	****************************************************************************
	* Start to shutdown the timerManager thread by set m_bDone flag to false.
	****************************************************************************
	**/
	
 	void StartShutDown();
 	
 	/**
	****************************************************************************
	* Create a new timer for the TimerManager to track. note that it is not
	* not initially set. Use DestroyTimer() to delete the timer when done using
	* it.
	* @param pHandler
	* 		handler will be invoked when the timer is fired.
	* @retVal unsigned long 
	* 		the ID of new created timer.
	****************************************************************************
	**/
		
 	unsigned long CreateTimer(TimerEventHandler * pHandler) ;
 	
 	/**
	****************************************************************************
	* Initial the new create timer
	* @param timerId
	* 		the Id of timer to be set.
	* @param offset
	*       number of milliseconds from current to trigger the timer
	* @param period
	* 		frequency in milliseconds to repeatly trigger the timer
	*       after initial fired. zero means it is one-time timer.
	* @retVal int
	* 		if timer was set successfully, return SUCCESS_OK else return
	* 		error code if  timerId is invalid.
	****************************************************************************
	**/
	
 	int SetTimer(unsigned long timerId,unsigned long offset,unsigned long period=0) ;
 	
 	/**
	****************************************************************************
	* Cancel the timer which provided in paramter timerId
	* @param timerId
	* 		the Id of timer to be set.
	* 
	* @retVal int
	* 		if timer was set successfully, return SUCCESS_OK else return
	* 		error code if  timerId is invalid.
	****************************************************************************
	**/
 	int CancelTimer(unsigned long timerId) ;
 	
 	/**
	****************************************************************************
	* Destroy the timer which provided in paramter timerId
	* @param timerId
	* 		the Id of timer to be set.
	* 
	* @retVal int
	* 		if timer was set successfully, return SUCCESS_OK else return
	* 		error code if  timerId is invalid.
	****************************************************************************
	**/
	
 	int DestroyTimer(unsigned long timerId) ;
 	
 	/**
	****************************************************************************
	* the method fires any pending timer events and determines when the next 
	* timer event will occur. It returns the time in milliseconds to the caller
	* to indicate how long the caller can sleep before the next timer event
	* ocurs.
	****************************************************************************
	**/	
 	virtual unsigned long processTimerEvent() ;
 	
private:
	static TimerManager * m_pTimerManager ;  /* pointer to sigleton of timerManager */
	
	static Mutex          m_sInstanceMutex ; /* lock during create and release sigleton */
	
	static int            m_sRefCount ;       /* Reference count of sigleton*/
	
	Mutex                 m_TimerListMutex ;  /* lock during to access timerListMap*/
	
	TimerListMap          m_timerList ;	       /* timer map. stores the created timer */
	
	bool                  m_bDone ;            /* flags to indicate weather the main thread loop is done */
	
	int                   m_iNextTimerId ;      /* next time Id which can be assigned */
 } ;
 #endif
