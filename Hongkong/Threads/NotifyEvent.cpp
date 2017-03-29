#include "NotifyEvent.h"

NotifyEvent::NotifyEvent()
{
	int ret = sem_init(&m_event,0,0) ;
	m_bInitialize = (0 == ret) ;
}
NotifyEvent::~NotifyEvent()
{
	if(m_bInitialize)
		sem_destroy(&m_event) ;
	m_bInitialize = false ;
}

int NotifyEvent::WaitNotify(unsigned long duration)
{
	int ret =0 ;
	if(NOTIFY_EVENT_TEST_LOCK == duration)
	{
		ret = sem_trywait(&m_event) ;
		if(0 == ret )
			return SUCCESS_OK ;
		return NOTIFY_EVENT_TRYWAIT_FAILED ;
	}
	if(NOTIFY_EVENT_WAIT_INFINITE == duration)
	{
		// wait forever
		sem_wait(&m_event) ;
		return SUCCESS_OK ;
		
	}
	struct timespec endTime ;
	clock_gettime(CLOCK_REALTIME,&endTime) ;
	endTime.tv_sec += duration/1000ul ;
	endTime.tv_nsec += (duration % 1000ul)* 1000000ul ;
	if ( endTime.tv_nsec >= 1000000000l ) 
	{
		endTime.tv_sec += 1;
		endTime.tv_nsec -= 1000000000l;
	}
	
	// start timed wait
	ret = sem_timedwait(&m_event,&endTime) ;
	if(0 != ret) //error occurs
	{
		int errorNo = errno ;
		switch(errorNo)
		{
		case ETIMEDOUT:
			ret = NOTIFY_EVENT_TIMEDOUT ;
			break ;
		case EINTR:
			ret = NOTIFY_EVENT_INTERRUPT ;
			break ;
		case EINVAL:
			ret = NOTIFY_EVENT_INVALID ;
			break ;
		}
	}
	return ret ;
}

void NotifyEvent::Notify(void)
{
	if(m_bInitialize)
		sem_post(&m_event) ;
}
