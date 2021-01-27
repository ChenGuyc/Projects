/***********************************
 * file name: slave_tasks.cpp      *
 * developer: Guy Chen             *
 * date: 30.11.20                  *
 * version 0.1                     *
 ***********************************/

#include <iostream>
#include "slave_tasks.hpp"

namespace hrd14
{

/*****************Read*********************/

Read::Read(std::shared_ptr<TaskArgs> args) :
           RequestEngineTask(args->priority),
           m_args(args), m_log(Handleton<Logger>::GetInstance())
{}

std::shared_ptr<RequestEngineTask> Read::Create(std::shared_ptr<TaskArgs> args)
{
    return (std::shared_ptr<RequestEngineTask> (new Read(args)));
}

void Read::Execute()
{
    m_args->driverData->m_status = m_args->storage->Read(m_args->driverData);
    
    m_args->driver->SendReply(m_args->driverData);
    m_log->Log("read from storage",
                __FILE__, __LINE__, false,
                Logger::LogLevel::INFO);
}

/*****************Write*********************/

Write::Write(std::shared_ptr<TaskArgs> args)
    : RequestEngineTask(args->priority), m_args(args),
      m_log(Handleton<Logger>::GetInstance())
{}

std::shared_ptr<RequestEngineTask> Write::Create(std::shared_ptr<TaskArgs> args)
{
    return (std::shared_ptr<RequestEngineTask> (new Write(args)));
}

void Write::Execute()
{
    m_args->driverData->m_status = m_args->storage->Write(m_args->driverData);

    if (!m_args->driverData->m_status)
    {
        m_args->driver->SendReply(m_args->driverData);
    }
    m_log->Log("write to storage",
                __FILE__, __LINE__, false,
                Logger::LogLevel::INFO);
}



}//hrd14
