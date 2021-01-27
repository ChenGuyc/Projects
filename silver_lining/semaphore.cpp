/***********************************
 * file name: semaphore.cpp        *
 * developer: Guy Chen             *
 * date: 30.11.20                  *
 * version 0.1                     *
 ***********************************/

#include <semaphore.h> // sem_t
#include <chrono>      //std::chrono
#include "semaphore.hpp"


namespace hrd14
{

Semaphore::Semaphore(int pshared, size_t value)
{
    if (sem_init(&m_sem, pshared, value))
    {
        throw std::invalid_argument("sem_init");
    }
}

Semaphore::~Semaphore()
{
    try
    {
        if (sem_destroy(&m_sem))
        {
            throw std::runtime_error("sem_destroy");
        }
    }
    catch (const std::exception& e)
    {
        //logger
    }
}


void Semaphore::Wait()
{
    if (sem_wait(&m_sem))
    {
        throw std::runtime_error("sem_wait");
    }
}

void Semaphore::Post()
{
    if (sem_post(&m_sem))
    {
        throw std::runtime_error("sem_post");
    }
}

void Semaphore::TryWait()
{
    if (sem_trywait(&m_sem))
    {
        throw std::runtime_error("sem_trywait");
    }
}

void Semaphore::TimedWait(const std::chrono::seconds& timeout)
{
    struct timespec absTimeout;
    if (clock_gettime(CLOCK_REALTIME, &absTimeout) == -1)
    {
        throw std::runtime_error("sem_timewait:clock_gettime");
    }
    
    absTimeout.tv_sec += timeout.count();

    if (sem_timedwait(&m_sem, &absTimeout))
    {
        throw std::runtime_error("sem_timewait");
    }
}

} //hrd14