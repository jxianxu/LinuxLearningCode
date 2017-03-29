/*
 * $Revision: 1.00 $
 * $Author: Jiang xianxu $
 * $Date: 2017/03/02 $
 *                                                                       
 */
/** @file
 *
 *	This file is a header file in which defines error codes.  
 */
 
/*
 ******************************************************************************
	Switches
 ******************************************************************************
 */
#ifndef ERROR_CODES_H
#define ERROR_CODES_H

#define SUCCESS_OK                         0
#define PTHREAD_ATTR_INIT_ERROR           -1
#define PTHREAD_SET_DETACHED_ERROR        -2
#define PTHREAD_SET_STACKSIZE_ERROR       -3
#define PTHREAD_CREATE_ERROR              -4
#define PTHREAD_SIGACTION_ERROR           -5


#define TIMER_MANAGER_INITIAL_ERROR        -6
#define TIMER_MANAGER_RUN_FAILED           -7
#define TIMER_REGISTER_FAILED              -8
#define TIMER_NOT_FOUND                    -9

#define PTHREAD_LOCK_FAILED                -10
#define PTHREAD_UNLOCK_FAILED              -11
#define PTHREAD_TRYLOCK_FAILED             -12
#define PTHREAD_TIMEDLOCK_FAILED           -13

#define NOTIFY_EVENT_TRYWAIT_FAILED        -14
#define NOTIFY_EVENT_TIMEDOUT              -15
#define NOTIFY_EVENT_INTERRUPT             -16
#define NOTIFY_EVENT_INVALID               -17

#define PRIORITY_QUEUE_FULL                -18
#define PRIORITY_QUEUE_EMPTY               -19
#define EVENTLOOP_THREAD_TIMERMGR_NULL     -20

#endif
