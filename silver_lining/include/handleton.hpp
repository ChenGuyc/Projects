
/*
Handleton ensures a class only has a single instance and provides global point of access to it

T must have a default private ctor
Handleton must be a friend class T
Handleton has self-destruction

Version        Date        Comments
0.1            07.12.20    mentor approval
0.2            08.12.20    macro added 
*/

#ifndef ILRD_HRD14_HANDELTON_HPP
#define ILRD_HRD14_HANDELTON_HPP


#include <mutex>    // std::mutex  
#include <atomic>   // std::atomic

#include "scope_lock.hpp"


namespace hrd14
{
    
// macro for handleton
#define INIT_HANDLETON(type)\
template<> std::atomic<type*> Handleton<type>::s_instance{nullptr};\
template<> std::mutex Handleton<type>::s_mutex = {};\


template <typename T>
class Handleton
{
public:
    Handleton()= delete;
    ~Handleton()= delete;
    Handleton(const Handleton&)= delete;
    Handleton& operator=(const Handleton&)= delete;
  
  	static T* GetInstance();
private:
    static std::mutex s_mutex;
    
    static std::atomic<T*> s_instance;

    static void FreeInstance();
};


template <typename T>
T* Handleton<T>::GetInstance()
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
void Handleton<T>::FreeInstance()
{
    delete s_instance.exchange(nullptr);
    
}   

}//hrd14

#endif //ILRD_HRD14_HANDELTON_HPP