/* - Provides a pool of threads that can be used to execute tasks,
*    using a PQueue of tasks. Size of pool defined upon creation by user.
*    Defailt #of threads is 4.
* Operations:
*  - AddTask() - adds a task to Pqueue
*  - Stop(timeout) - default stop, stops all active threads and shuts down,     
*                    possible loss of info
*  - Stop() - waits for active threads to finish their tasks and then shuts
*             down. Posible  loss of info.
*  - SetSize() - modify pool size
*  - Suspend() - pauses activity, waits on active threads to finish tasks 
*                before pause. No loss of info
*  - Resume() - resumes activity after suspend was activated 
*
* Each new task should receive it's priority upon creation.
* Tasks inheriting from this abstract class must override the virtual Execute 
* function.
* ADMIN priority should not be used for normal tasks, and it is meant to create 
* a stop task, to shutdown system gracefully
* 
* Version         Date        Comments
* 0.1             14.12.20      
*/

#ifndef ILRD_HRD14_THREAD_POOL_HPP
#define ILRD_HRD14_THREAD_POOL_HPP

#include <chrono>               // std::chrono
#include <vector>               // std::vector
#include <memory>               // std::shared_ptr
#include <thread>               // std::thread
#include <condition_variable>   // std::condition_variable

#include "tp_task.hpp"
#include "WPQueue.hpp"


namespace hrd14
{

class ThreadPool
{
public:
    static const size_t defaultSize = 1;

    //must check size, if 0 - size = 1
    explicit ThreadPool(size_t size = std::thread::hardware_concurrency());
    ~ThreadPool();
    ThreadPool(const ThreadPool& other) = delete;
    ThreadPool& operator=(const ThreadPool& other) = delete;

    void AddTask(std::shared_ptr<TPTask> task);

    void Stop();
    void Stop(std::chrono::seconds timeout);

    void SetSize(size_t size);

    void Suspend();
    void Resume();

private:
    void HandleTask();
    
    std::vector<std::thread> m_pool;
    WPQueue< std::shared_ptr<TPTask> > m_pqueue;
    std::mutex m_mutex;
    std::condition_variable m_suspend;

    size_t m_size;
};
}//namespace hrd14

#endif //ILRD_HRD14_THREAD_POOL_HPP

