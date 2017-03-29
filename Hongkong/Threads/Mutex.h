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
	Switches
 ******************************************************************************
 */
 #ifndef MUTEX_H
 	#define MUTEX_H
 
 #include <pthread.h>
 #include <sys/types.h>
 #include <stdbool.h>
 #include <time.h>
 #include "errorCodes.h"
 /*
 ******************************************************************************
	Macros
 ******************************************************************************
 */
 
 
 /*
 ******************************************************************************
	Classes
 ******************************************************************************
 */
 class Mutex
 {
 public:
 	/*
 	******************************************************************************
	* Constructor
 	******************************************************************************
 	*/
 	Mutex(int mutextype = PTHREAD_MUTEX_NORMAL) ;
 	/*
 	******************************************************************************
	* destructor
 	******************************************************************************
 	*/
 	~Mutex() ;
 	
 	/*
 	******************************************************************************
	* Obtain the access to resource, the operation will be blocked until the
	* resource becomes available.
 	******************************************************************************
 	*/
 	int Lock() ;
 	/*
 	******************************************************************************
	* Release the acccess to resource.
 	******************************************************************************
 	*/
 	int Unlock() ;
 	/*
 	******************************************************************************
	* Try to obtain the access to resource. If the resource is locked by other
	* thread,it return EBUSY, else it lock the resource and return 0.
 	******************************************************************************
 	*/
 	int Trylock() ;
 	/*
 	******************************************************************************
	* Obtain the access to resource,if the resource is locked by other thread
	* it will wait a given time, if it still locked by other thread after a given
	* time, it return error: ETIMEOUT
	* Note: the given time 'tsptr' is absolutely time
 	******************************************************************************
 	*/
 	int TimedLock(const struct timespec* tsptr) ;

 	/*
 	******************************************************************************
	* Obtain the mutex type
 	******************************************************************************
 	*/
 	int  GetMutextTypeAttribute() ;
 	/*
 	******************************************************************************
	* Set the mutex type
 	******************************************************************************
 	*/
 	void SetMutexTypeAttribute(int type) ;
 	 
 	
 	/*
 	******************************************************************************
	* Set the process shared attribute of Mutex
 	******************************************************************************
 	*/
 	void SetProcessSharedAttribute(int pshared); 
 	
 	/*
 	******************************************************************************
	* Get the process shared attribute of Mutex
 	******************************************************************************
 	*/
 	int GetProcessSharedAttribute() ;
 	
 	/*
 	******************************************************************************
	* Set the Robust attribute of Mutex
 	******************************************************************************
 	*/
 	void SetRobustAttribute(int robust) ;
 	
 	/*
 	******************************************************************************
	* Get the Robust attribute of Mutex
 	******************************************************************************
 	*/
 	int GetRobustAttribute() ;
 	
 	/*
 	******************************************************************************
	* Get the Last Error information
 	******************************************************************************
 	*/
 	int GetLastError(){return m_iLastError ;} 
 private:
 	pthread_mutex_t      m_mutex;        /*Linux mutex*/
 	
 	int                  m_iLastError  ;  /*store the last error no*/
 	
 };
 
 
 #endif
