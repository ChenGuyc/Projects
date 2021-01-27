/*
 *  Wrapper API for different mutex types, RAII mechanism built in
 *  
 *  mutex is locked on ctor and automatically unlocked at the end of the scope
 *  Author: Hen Hassid
 *  Version     Date            Comment
 *  0.1         10.11.2020      mentor aproval
 *  1.0         07.11.2020      C++11 modification
 */

#include <pthread.h>    // pthread_mutex_t
#include <mutex>        // std::mutex
#include <stdexcept>    // runtime_error
#include <exception>    // exception

#ifndef ILRD_HRD14_SCOPE_LOCK_HPP
#define ILRD_HRD14_SCOPE_LOCK_HPP

namespace hrd14
{

template <typename Mutex>
class ScopeLock
{
public:
    explicit ScopeLock(Mutex& mutex);
    ~ScopeLock();

    ScopeLock(const Mutex& other) = delete;
    ScopeLock<Mutex>& operator=(const Mutex& other) = delete;
private:

    Mutex& m_mutex;
};

template <typename Mutex>
ScopeLock<Mutex>::ScopeLock(Mutex &mutex) : m_mutex(mutex)
{
    m_mutex.lock();
}

template <>
inline ScopeLock<pthread_mutex_t>::ScopeLock(pthread_mutex_t &mutex) : m_mutex(mutex)
{
    if (pthread_mutex_lock(&m_mutex))
    {
        throw std::runtime_error("pthread_mutex_lock failed");
    }
}

// exception safe
template <typename Mutex>
ScopeLock<Mutex>::~ScopeLock()
{
    m_mutex.unlock();
}

template <>
inline ScopeLock<pthread_mutex_t>::~ScopeLock()
{
    try
    {
        if (pthread_mutex_unlock(&m_mutex))
        {
            throw std::runtime_error("pthread_mutex_unlock failed");
        }
    }
    catch (const std::exception& e)
    {
        // TO DO Log
    }
}

}//hrd14

#endif // ILRD_HRD14_SCOPE_LOCK_HPP