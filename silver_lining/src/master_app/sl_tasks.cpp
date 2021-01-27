/***********************************
 * file name: sl_tasks.cpp         *
 * developer: Guy Chen             *
 * date: 28.12.20                  *
 * version 0.1                     *
 ***********************************/


#include <iostream>
#include "sl_tasks.hpp"

namespace hrd14
{

Read::Read(std::shared_ptr<TaskArgs> args) : RequestEngineTask(args->priority), m_args(args)
{}

std::shared_ptr<RequestEngineTask> Read::Create(std::shared_ptr<TaskArgs> args)
{
    return (std::shared_ptr<RequestEngineTask> (new Read(args)));
}

void Read::Execute()
{

    std::cout << "Request for read of size " << m_args->driverData->m_len 
                                             << std::endl;
    
    m_args->driverData->m_status = m_args->storage->Read(m_args->driverData);
    m_args->driver->SendReply(m_args->driverData);
    
}

/****************************************/

Write::Write(std::shared_ptr<TaskArgs> args)
    : RequestEngineTask(args->priority), m_args(args)
{}

std::shared_ptr<RequestEngineTask> Write::Create(std::shared_ptr<TaskArgs> args)
{
    return (std::shared_ptr<RequestEngineTask> (new Write(args)));
}

void Write::Execute()
{
    ;
    std::cout << "Request for write of size " << m_args->driverData->m_len 
                                              << std::endl;

    m_args->driverData->m_status = m_args->storage->Write(m_args->driverData);
    
    m_args->driver->SendReply(m_args->driverData);
}

/****************************************/

Disconnect::Disconnect(std::shared_ptr<TaskArgs>  args) : RequestEngineTask(args->priority), m_args(args)
{}

std::shared_ptr<RequestEngineTask> Disconnect::Create(std::shared_ptr<TaskArgs> args)
{
    return (std::shared_ptr<RequestEngineTask> (new Disconnect(args)));
}

void Disconnect::Execute()
{
    
    std::cout << "Received a disconnect request" << std::endl;

    m_args->driver->Disconnect();

    m_args->driver->SendReply(m_args->driverData);
}

/******************/

Flush::Flush(std::shared_ptr<TaskArgs> args) : RequestEngineTask(args->priority), m_args(args)
{}

std::shared_ptr<RequestEngineTask> Flush::Create(std::shared_ptr<TaskArgs> args)
{
    return (std::shared_ptr<RequestEngineTask> (new Flush(args)));
}

void Flush::Execute()
{
   
    std::cout << "Received a flush request" << std::endl;

    m_args->driver->SendReply(m_args->driverData);
}

/******************/

Trim::Trim(std::shared_ptr<TaskArgs> args) : RequestEngineTask(args->priority), m_args(args)
{}

std::shared_ptr<RequestEngineTask> Trim::Create(std::shared_ptr<TaskArgs> args)
{
    return (std::shared_ptr<RequestEngineTask> (new Trim(args)));
}

void Trim::Execute()
{
   
    std::cout << "Received a trim request" << std::endl;

    m_args->driver->SendReply(m_args->driverData);
}

/******************/


}//hrd14
