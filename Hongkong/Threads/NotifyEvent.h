#ifndef NOTIFY_EVENT_H
#define NOTIFY_EVENT_H

#include <semaphore.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include "errorCodes.h"

#define NOTIFY_EVENT_WAIT_INFINITE 0xFFFFFFFFul
#define NOTIFY_EVENT_TEST_LOCK     0

class NotifyEvent
{
public:
	NotifyEvent() ;
	~NotifyEvent() ;
	
	int WaitNotify(unsigned long duration) ;
	void Notify(void) ;
protected:
	sem_t m_event ;
	bool m_bInitialize ;
};
#endif
