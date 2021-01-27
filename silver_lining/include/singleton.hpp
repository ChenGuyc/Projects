
/*
Singleton ensures a class only has a single instance and provides global point of access to it

T must have a default private ctor
Singleton must be a friend class T
Singleton has self-destruction

Version        Date        Comments
0.1            7.12.20     mentor approval

*/

#ifndef ILRD_HRD14_SINGLETON_HPP
#define ILRD_HRD14_SINGLETON_HPP

#include <mutex>    // std::mutex  
#include <atomic>   // std::atomic
#include <memory>   // std::sh
#include "scope_lock.hpp"

namespace hrd14
{
template <typename T>
class Singleton
{
public:
    Singleton()= delete;
    ~Singleton()= delete;
    Singleton(const Singleton&)= delete;
    Singleton& operator=(const Singleton&)= delete;
  
  	static T* GetInstance();
private:
    static std::mutex s_mutex;
    
    static std::atomic<T*> s_instance;

    static void FreeInstance();
};

template <typename T>
std::mutex Singleton<T>::s_mutex;

template <typename T>
std::atomic<T*> Singleton<T>::s_instance;

template <typename T>
T* Singleton<T>::GetInstance()
{
    T* temp = s_instance.load(std::memory_order_relaxed);
    
    std::atomic_thread_fence(std::memory_order_acquire);

    if (nullptr == temp)
    {
        ScopeLock<std::mutex> lock(s_mutex);

        temp = s_instance.load(std::memory_order_relaxed);
        
        if (nullptr == temp)
        {
            temp = new T;
            std::atomic_thread_fence(std::memory_order_relaxed);
            s_instance.store(temp, std::memory_order_relaxed);
            
            atexit(FreeInstance);
        }
    }
    
    return (temp);
}

template <typename T>
void Singleton<T>::FreeInstance()
{
    delete s_instance.exchange(nullptr);
}

}//hrd14

#endif //ILRD_HRD14_SINGLETON_HPP