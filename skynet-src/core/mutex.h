#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "noncopyable.h"
#include <assert.h>
#include <pthread.h>

class MutexLock : noncopyable {
public:
    MutexLock() {
        pthread_mutex_init(&mutex_, NULL)
    }
    
    ~MutexLock() {
        pthread_mutex_destroy(&mutex_)
    }

    void lock()
    {
        pthread_mutex_lock(&mutex_);
    }

    void unlock()
    {
        pthread_mutex_unlock(&mutex_);
    }

    pthread_mutex_t* getPthreadMutex() /* non-const */
    {
        return &mutex_;
    }

private:
    pthread_mutex_t mutex_;
};

#endif