#ifndef __SINGLETION_H__
#define __SINGLETION_H__

#include "noncopyable.h"
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

namespace detail
{
    template<typename T>
    struct has_no_destroy
    {
        #ifdef __GXX_EXPERIMENTAL_CXX0X__
        template <typename C> static char test(decltype(&C::no_destroy));
        #else
        template <typename C> static char test(typeof(&C::no_destroy));
        #endif
        template <typename C> static int32_t test(...);
        const static bool value = sizeof(test<T>(0)) == 1;
    };
}

template <typename T>
class Singletion : noncopyable {
public:
    static T& install() {
        pthread_once(&ponce_, &Singletion::init);
        assert(value_ != NULL);
        return *value_;
    }

private:
    static void init() {
        value_ = new T();
        if (!detail::has_no_destroy::value) {
            ::atexit(destroy);
        }
    }
    static void destroy()
    {
        typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
        T_must_be_complete_type dummy; (void) dummy;

        delete value_;
        value_ = NULL;
    }

private:
    static pthread_once_t ponce_;
    static T*             value_;
};

template <typename T>
pthread_once_t Singletion<T>::ponce_ = PTHREAD_ONCE_INIT;

template <typename T>
T* Singletion<T>::value_ = NULL;

#endif