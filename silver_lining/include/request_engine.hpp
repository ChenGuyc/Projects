/*
* A Request Engine represents the framework and provides the following functionalities:
* config task - configurates the task based on a key and a create function
* config gateway - configurates the getways and saves them in a vector 
* start - handles the incoming requests based on Reactor design pattern
* stop - stops the request engine
* 1. Configuration - Tasks, Inpout source (GWs) 
  2. Async, Thread pool for async handling tasks .
  2. P&P 
  3. Failsafe and logging services    

* while creating an object user should provide the full path for the plugins folder, otherwise,
* a folder will be created automatcally in ./plugins path  
*
* Version         Date        Comments
* 0.1             23.12.20     API mentor approved
*/


#ifndef ILRD_HRD14_REQUEST_ENGINE_HPP
#define ILRD_HRD14_REQUEST_ENGINE_HPP

#include <unistd.h>     // STDIN_FILENO

#include "re_task.hpp"
#include "re_gateway.hpp"
#include "handleton.hpp"
#include "factory.hpp"
#include "logger.hpp"
#include "thread_pool.hpp"

//#include p&p wraper

namespace hrd14
{

template <typename Key, typename Args>
class RequestEngine final
{
public:
    //...
    explicit RequestEngine(size_t numOfThreads =                    
                           std::thread::hardware_concurrency(),
                           const std::string& pluginsPath = "./plugins");
    RequestEngine(const RequestEngine&)= delete;
    RequestEngine& operator=(const RequestEngine&) = delete;
    ~RequestEngine();

    using CreateFunc = 
        std::function<std::shared_ptr<RequestEngineTask>(Args args)>;
    
    void ConfigTask(Key key, CreateFunc createFunc);
    void ConfigGateway(std::shared_ptr<
                                        RequestEngineGateway< Key, Args>
                                      > gateway);
    void Start();
    void Stop();
   
private:
    const std::string& m_path;
    Factory<RequestEngineTask, Key, Args>* m_factory; //handelton
    ThreadPool m_threadPool;
    //p&p wraper... //dirmonitor dllmontor

    std::vector<std::shared_ptr<RequestEngineGateway<Key, Args>>> m_gateways;

    Logger* m_log;

    bool m_isRunning;
};

/***************************/
template <typename Key, typename Args>
RequestEngine<Key, Args>::RequestEngine(size_t numOfThreads,
                                        const std::string& pluginsPath)
    : m_path(pluginsPath),
      m_factory(Handleton< Factory
                           <RequestEngineTask, Key, Args>
                         >::GetInstance()),
      m_threadPool(numOfThreads),
      m_log(Handleton< Logger >::GetInstance()),
      m_isRunning(true)
{}
/***************************/
template <typename Key, typename Args>
RequestEngine<Key, Args>::~RequestEngine()
{
    if(m_isRunning)
    {
        Stop();
    }
}
template <typename Key, typename Args>
void RequestEngine<Key, Args>::ConfigTask(Key key, CreateFunc createFunc)
{
    m_log->Log("Add task",
               __FILE__,
               __LINE__,
               false,
               Logger::LogLevel::INFO);

    m_factory->Add(key, createFunc);
}
/***************************/
template <typename Key, typename Args>
void RequestEngine<Key, Args>::ConfigGateway
    (std::shared_ptr<RequestEngineGateway< Key, Args> > gateway)
{
    m_gateways.emplace_back(gateway);    
}

/***************************/

template <typename Key, typename Args>
void RequestEngine<Key, Args>::Start()
{
    //std::cout << "in select\n";
    fd_set set;
    fd_set currSet;

    FD_ZERO(&set);
    FD_ZERO(&currSet);
    
    for (auto &gateway : m_gateways)
    {
        FD_SET(gateway->GetFD(), &set);
        std::cout << gateway->GetFD()<<"\n";
    }

    FD_SET(STDIN_FILENO, &set);

    while (m_isRunning)
    {
        currSet = set;
        
        if (-1 == select(FD_SETSIZE, &currSet, NULL, NULL, NULL))
        {
            if (errno == EINTR)
            {
                continue;
            }
            
            m_log->Log("select failed", __FILE__, __LINE__, false);

            throw std::runtime_error("select failed");
        }
        else
        {
            std::cout << "in select\n";
            for (auto& gateway : m_gateways)
            {
                
                if (FD_ISSET(gateway->GetFD(), &currSet))
                {   
                    m_log->Log("gateway is set in select", __FILE__, __LINE__, false, Logger::LogLevel::INFO);
                    auto pair = gateway->Read();

                    auto task = m_factory->Create(pair.first, pair.second);
                    
                    m_threadPool.AddTask(task);
                }
            }
        }
        
        
    }
}


/***************************/
template <typename Key, typename Args>
void RequestEngine<Key, Args>::Stop()
{
    m_isRunning = false;
    std::cout << "Request Engine stop\n";
    m_log->Log("in RequestEngine::Stop", __FILE__, __LINE__, false, Logger::LogLevel::INFO);
    for (auto &gateways : m_gateways)
    {
        gateways->Stop();
    }
}

/***************************/

}//namespace hrd14

#endif //ILRD_HRD14_REQUEST_ENGINE_HPP

