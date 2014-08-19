#ifndef THREADLOCK_H
#define THREADLOCK_H

#include "pthread.h"

class ThreadLock
{
private:
	pthread_mutex_t mutexlock;
public:
	ThreadLock();
	~ThreadLock();
	void lock();
	void unlock();
};

#endif // !THREADLOCK_H
