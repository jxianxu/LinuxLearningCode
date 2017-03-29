/*
 * $Revision: 1.00 $
 * $Author: Jiang xianxu $
 * $Date: 2017/03/02 $
 *                                                                       
 */
/** @file
 *
 *	This file defines the JiangEventHandler class which inherit from .  This class defines
 *  the interface for event handler.
 */
 
/*
 ******************************************************************************
	Switches
 ******************************************************************************
 */
 #ifndef JIANG_EVENT_HANDLER_H
 #define JIANG_EVENT_HANDLER_H
 
 #include "TimerManager.h"
 
 class JiangEventHandler : public TimerEventHandler
 {
 public:
 	virtual void DoTimerEvent(unsigned long timerId) ;
 };
 
 #endif
