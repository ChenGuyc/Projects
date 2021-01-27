/*
* Thread-safe wrapper for STL priority queue.

* T         - type of stored element
* Container - type of container used to store elements, default value = std::vector<T>
* Compare   - compare function providing  a strict weak ordering, default value = std::less<typename Container::value_type> 
* 
* - If default compare function is used, T must provide comparison operator < 
*
* -A user-provided Compare can be supplied to change the ordering, otherwise default  Compare function will be used
*
Version         Date        Comments
0.1             13.12.20      API mentor approved
*/

#ifndef ILRD_HRD14_WPQUEUE_HPP
#define ILRD_HRD14_WPQUEUE_HPP

#include <queue>       // std::prirority_queue
#include <vector>      //std:: vector
#include <functional>  // std::less
#include <chrono>      // std::crono
#include <mutex>       //std::mutex

#include "scope_lock.hpp"
#include "semaphore.hpp" //semaphore


#include <iostream>
namespace hrd14
{

template <typename T, 
          typename Container = std::vector<T>, 
          typename Compare = std::less<typename Container::value_type>>

class WPQueue
{

public:
    
    explicit WPQueue(const Compare& compare = Compare());
    WPQueue(const WPQueue&)= delete;
    WPQueue& operator=(const WPQueue&) = default;
    ~WPQueue() = default;

    void Push(const T& value);

    //blocking and waitable function, if no timeout given - infinite run
    void Pop(T& retVal);
    bool Pop(T& retVal, std::chrono::seconds timeout);
    
    // return true if empty, false if not
    bool IsEmpty() const;
    size_t Size() const;

private:

    std::priority_queue<T, Container, Compare> m_queue;
    mutable std::mutex m_mutex;
    Semaphore m_sem; 
};


/********************/
template <typename T, typename Container, typename Compare>
WPQueue<T, Container, Compare>::WPQueue(const Compare& compare)
{
    m_queue = std::priority_queue<T, Container, Compare>(compare);
}

/********************/

template <typename T, typename Container, typename Compare>
void WPQueue<T, Container, Compare>::Push(const T& value)
{
    ScopeLock<std::mutex> lock(m_mutex);
    m_queue.push(value);
    try
    {
        m_sem.Post();
    }
    catch(std::runtime_error& e)
    {
        //logger
    }
}

/********************/

template <typename T, typename Container, typename Compare>
void WPQueue<T, Container, Compare>::Pop(T& retVal)
{
    try
    {
        m_sem.Wait();
        ScopeLock<std::mutex> lock(m_mutex);
        retVal = m_queue.top();
        m_queue.pop();

    }
    catch(std::runtime_error& e)
    {
        //logger
    }
}

/********************/

template <typename T, typename Container, typename Compare>
bool WPQueue<T, Container, Compare>::Pop(T& retVal,
                                         std::chrono::seconds timeout)
{
    try 
    {
        m_sem.TimedWait(timeout);
        ScopeLock<std::mutex> lock(m_mutex);
        retVal = m_queue.top();
        m_queue.pop();
    }
    catch (std::runtime_error& e)
    {
        return (false);
    }

    return (true);
}

/********************/

template <typename T, typename Container, typename Compare>
bool WPQueue<T, Container, Compare>::IsEmpty() const
{
    ScopeLock<std::mutex> lock(m_mutex);
    return (m_queue.empty());
}

/********************/

template <typename T, typename Container, typename Compare>
size_t WPQueue<T, Container, Compare>::Size() const
{
    ScopeLock<std::mutex> lock(m_mutex);
    return (m_queue.size());
}

}//namespace hrd14

#endif //ILRD_HRD14_WPQUEUE_HPP
