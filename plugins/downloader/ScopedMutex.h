#ifndef __ScopedMutex__
#define __ScopedMutex__


extern "C" {
#include <pthread.h> 
}

class ScopedMutex
{
public:
	inline ScopedMutex(pthread_mutex_t * mutex);
	inline ~ScopedMutex();

private:
	pthread_mutex_t * _mutex;
};

//////////////////////////////////////////////////////////////////////////

ScopedMutex::ScopedMutex(pthread_mutex_t * mutex)
	: _mutex(mutex)
{
	pthread_mutex_lock(mutex);
}

ScopedMutex::~ScopedMutex()
{
	pthread_mutex_unlock(_mutex);
}

#endif
