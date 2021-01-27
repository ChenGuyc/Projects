
/***********************************
 * file name: thread_pool.cpp      *
 * developer: Guy Chen             *
 * date: 14.12.20                  *
 * version 0.1                     *
 ***********************************/

#include <memory>               // std::shared_ptr
#include <unistd.h>             // sleep
#include <exception>
#include "thread_pool.hpp"
#include "logger.hpp"

namespace hrd14
{



class StopException : public std::domain_error
{
public:
    explicit StopException(const std::string& errMsg) :domain_error(errMsg) {}
    virtual ~StopException() = default;
};

class SuspendException : public std::domain_error
{
public:
    explicit SuspendException(const std::string& errMsg) :domain_error(errMsg) {}
    virtual ~SuspendException() = default;
};
/************StopTask************/

class StopTask: public TPTask
{
public:
    StopTask(): TPTask(ADMIN) {}
    ~StopTask() = default;

private:
    void Execute()
    {
        throw StopException("stop");
    }
};

/************SuspendTask************/

class SuspendTask: public TPTask
{
public:
    SuspendTask(): TPTask(ADMIN) {}
    ~SuspendTask() = default;

private:
    void Execute()
    {
        throw StopException("suspended");
    }
};

/************ctor***********/
ThreadPool::ThreadPool(size_t size)
{
    if (!size)
    {
        size = ThreadPool::defaultSize;
    }

    m_size = size;

    for(size_t i = 0; i < size; ++i)
    {
        m_pool.push_back(std::thread(&ThreadPool::HandleTask, this));
    }
}

/************dtor***********/

ThreadPool::~ThreadPool()
{
    Stop();
}

/***************************/
/********HandleTask*********/

void ThreadPool::HandleTask()
{
    Logger* g_logger = Handleton<Logger>::GetInstance();
    std::shared_ptr<TPTask> task;
    bool stopped= false;
    try
    {
        while (!stopped)
        {
            m_pqueue.Pop(task);
            
            task->Execute();
        }
    }
    catch (StopException& e)
    {
        stopped = true;
        g_logger->Log(e.what(),  __FILE__, __LINE__, false, Logger::LogLevel::INFO);
    }
    catch (SuspendException& e)
    {
        g_logger->Log(e.what(),  __FILE__, __LINE__, false, Logger::LogLevel::INFO);
        std::unique_lock<std::mutex> lock(m_mutex);
        m_suspend.wait(lock);
    }
    catch(...)
    {
        g_logger->Log("unknown exception",  __FILE__, __LINE__);
    }
}

/**********AddTask**********/

void ThreadPool::AddTask(std::shared_ptr<TPTask> task)
{
    m_pqueue.Push(task);
}

/*********Stop***********/

void ThreadPool::Stop()
{
    for (size_t size = 0; size< m_size; ++size)
    {
        std::shared_ptr<TPTask> stopTask(new StopTask);
        AddTask(stopTask);
    }
    for (auto& thread : m_pool)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}

/********Agressive Stop************/

void ThreadPool::Stop(std::chrono::seconds timeout)
{
    std::this_thread::sleep_for(timeout);

    pthread_t id;
    for (auto& thread : m_pool)
    {
        id = thread.native_handle();
        thread.detach();

        pthread_cancel(id);
    }
}

/**********SetSize**********/

void ThreadPool::SetSize(size_t size)
{
    size_t currSize = m_size;
    if (currSize > size)
    {
        for (size_t num = size; num < size; ++num)
        {
            std::shared_ptr<TPTask> stopTask(new StopTask);
            AddTask(stopTask);
        }
    }
    else if (currSize < size)
    {
        for (size_t num = currSize; num < size; ++num)
        {
            m_pool.push_back(std::thread(&ThreadPool::HandleTask, this));
        }
    }
    m_size = size;
}

/*********Suspend***********/

void ThreadPool::Suspend()
{
    for(size_t size = 0; size < m_size; ++size)
    {
        std::shared_ptr<TPTask> suspendTask(new SuspendTask);
        AddTask(suspendTask);
    }
}

/*********Resume***********/

void ThreadPool::Resume()
{
    m_suspend.notify_all();
}

/********************/
/********************/

}//hrd14

