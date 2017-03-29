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
 
/*
 ******************************************************************************
	Switches
 ******************************************************************************
 */
 #ifndef PRIORITY_QUEUE_H
 #define PRIORITY_QUEUE_H
 
 /*
 ******************************************************************************
	Header file
 ******************************************************************************
 */
 #include <map>
 #include "Mutex.h"
 #include <stdbool.h>
 
 /*
 ******************************************************************************
	Macros
 ******************************************************************************
 */
 
 #define PRIORITY_NO_PRIORITY          0
 #define PRIORITY_VERY_LOW             1
 #define PRIORITY_LOW                  2
 #define PRIORITY_LOWER_MEDIUM         3
 #define PRIORITY_UPPER_MEDIUM         4
 #define PRIORITY_HIGH                 5
 #define PRIORITY_HIGHEST              6
 
 /*
 ******************************************************************************
	structs definitions
 ******************************************************************************
 */
 
 struct MessageNode
 {
 	MessageNode()
 	{
 		message = 0 ;
 		wParam = 0 ;
 		lParam = 0 ;
 	}
 	
 	MessageNode(unsigned long msg,unsigned long wP,unsigned long lP)
 	{
 		message = msg ;
 		wParam = wP ;
 		lParam = lP ;
 	}
 	unsigned long message ;
 	unsigned long wParam ;
 	unsigned long lParam ;
 };
 
 struct PriorityQueueKey
 {
 	PriorityQueueKey()
 	{
 		priority = 0 ;
 		MsgNodeId = 0 ;
 		
 	}
 	
 	PriorityQueueKey(int pri,int msgNodeId)
 	{
 		priority = pri ;
 		MsgNodeId = msgNodeId ;
 	}

 	int priority ;
 	int MsgNodeId ;
 };
 struct PriorityQueueCompare
 {
 	int operator()(const PriorityQueueKey& key1, const PriorityQueueKey& key2)
 	{
 		if(key1.priority < key2.priority)
 			return 0 ;
 		else if(key1.priority > key2.priority)
 			return 1 ;
 		else
			return (key1.MsgNodeId < key2.MsgNodeId)? 1 : 0 ;
 		
 	}
 };
 
  /*
 ******************************************************************************
	typedef definitions
 ******************************************************************************
 */

 typedef std::multimap<PriorityQueueKey,MessageNode,PriorityQueueCompare> PriorityQueueMap ;
 
 /*
 ******************************************************************************
	classes definitions
 ******************************************************************************
 */
 
 class PriorityQueue : protected PriorityQueueMap
 {
 public:
 	/**
	****************************************************************************
	* Constructors
	****************************************************************************
	**/
 	PriorityQueue():PriorityQueueMap(),m_iNextNodeId(0),m_iMaxQueueDepth(0),m_iQueueSize(0)
 	{
 	
 	}
 	PriorityQueue(int nextNodeId,int maxDepth,int size):PriorityQueueMap(),m_iNextNodeId(nextNodeId),m_iMaxQueueDepth(maxDepth),
 	m_iQueueSize(size)
 	{
 	
 	}
 	/**
	****************************************************************************
	* Push Functions. it push a message to priority queue
	****************************************************************************
	**/
 	int Push(unsigned long msg,unsigned long wP,unsigned long lP,int priority = PRIORITY_LOW) ;
 	int Push( MessageNode node, int priority = PRIORITY_LOW) ;
 	/**
	****************************************************************************
	* Pop Functions. it pop a message from priority queue according to priority
	****************************************************************************
	**/
 	int Pop( MessageNode& node) ;
 	int Pop(unsigned long& msg,unsigned long& wP,unsigned long& lP);
 	
 	/**
	****************************************************************************
	* Set the max queue depth of the priority queue.
	****************************************************************************
	**/
 	void SetMaxQueueDepth(int depth){ m_iMaxQueueDepth = depth ; } 
 	
 	/**
	****************************************************************************
	* Get the max queue depth of the priority queue.
	****************************************************************************
	**/
 	int  GetMaxQueueDepth() { return m_iMaxQueueDepth ;}
 	
 	/**
	****************************************************************************
	* Get the current queue depth of the priority queue.
	****************************************************************************
	**/
 	int GetQueueSize(){return m_iQueueSize ;}
 	
 	/**
	****************************************************************************
	* If the value of m_iQueueSize equal to 0, it returns true eles returns false
	****************************************************************************
	**/
 	bool IsEmpty() {return (0 == GetQueueSize()) ;}
 	
 	/**
	****************************************************************************
	* If the value of m_iQueueSize equal to m_iMaxQueueDepth, it returns true 
	* eles returns false
	****************************************************************************
	**/
 	bool IsFull(){return ( m_iQueueSize >= m_iMaxQueueDepth) ;}
 
 protected:
 	Mutex             m_QueueMutex ;        /* Lock priority queue, when access the queue */
 	
 	int               m_iNextNodeId ;       /* the next message node Id will be assigned */
 	
 	int               m_iMaxQueueDepth ;    /* the maxmum depth of the priority queue*/
 	
 	int               m_iQueueSize ;        /* stores the current depth of the priority queue */
 	
 };

 #endif
