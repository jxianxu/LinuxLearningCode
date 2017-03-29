/*
 * $Revision: 1.00 $
 * $Author: Jiang xianxu $
 * $Date: 2017/03/03 $
 *                                                                       
 */
/** @file
 *
 *	This file defines the PriorityQueue class.  This class defines
 *  the interface about priority queue for message. you can push 
 *  your message to queue and pop it from the queue
 */
 
#include "PriorityQueue.h"


/**
****************************************************************************
* PriorityQueue::Push
****************************************************************************
**/
int PriorityQueue::Push(unsigned long msg,unsigned long wP,unsigned long lP,int priority)
{

	struct MessageNode node(msg,wP,lP) ;
	return Push(node,priority) ;	
}

/**
****************************************************************************
* PriorityQueue::Push
****************************************************************************
**/

int PriorityQueue::Push( MessageNode node,int priority)
{
	int ret = SUCCESS_OK ;
	m_QueueMutex.Lock() ;
	if(m_iMaxQueueDepth != 0 && IsFull() )
	{
		m_QueueMutex.Unlock() ;
		return PRIORITY_QUEUE_FULL ;	
	}
	
	PriorityQueueKey key ;
	key.priority = priority ;
	key.MsgNodeId = m_iNextNodeId++ ;
	
	insert(std::make_pair(key,node)) ;
	m_iQueueSize ++ ;
	
	m_QueueMutex.Unlock() ;
	return ret ;
}

/**
****************************************************************************
* PriorityQueue::Pop
****************************************************************************
**/

int PriorityQueue::Pop( MessageNode& node)
{
	m_QueueMutex.Lock() ;
	
	if(IsEmpty() )
	{
		m_QueueMutex.Unlock() ;
		return PRIORITY_QUEUE_EMPTY ;
	}
	
	iterator front = begin() ;
	node = front->second ;
	m_iQueueSize -- ;
	erase(front) ;
	m_QueueMutex.Unlock() ;	
	
	return SUCCESS_OK ;
	
}

/**
****************************************************************************
* PriorityQueue::Pop
****************************************************************************
**/

int PriorityQueue::Pop(unsigned long& msg,unsigned long& wP,unsigned long& lP)
{
	struct MessageNode node ;
	int ret = Pop(node) ;
	if(SUCCESS_OK == ret)
	{
		msg = node.message ;
		wP = node.wParam ;
		lP = node.lParam ;
	}
	return ret ;
	
}
