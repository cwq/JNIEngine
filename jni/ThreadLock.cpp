#include "ThreadLock.h"

ThreadLock::ThreadLock() {
	pthread_mutex_init(&mutexlock, NULL);
}

ThreadLock::~ThreadLock() {
	pthread_mutex_destroy(&mutexlock);
}

void ThreadLock::lock() {
	pthread_mutex_lock(&mutexlock);
}

void ThreadLock::unlock() {
	pthread_mutex_unlock(&mutexlock);
}