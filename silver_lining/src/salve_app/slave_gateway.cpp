/***********************************
 * file name: slave_gateway.cpp    *
 * developer: Guy Chen             *
 * date: 06.01.21                  *
 * version 0.1                     *
 ***********************************/

#include <iostream>
#include "slave_gateway.hpp"

namespace hrd14
{

SlaveGateway::SlaveGateway(std::shared_ptr<Storage> storage)
    : m_slaveDriver(std::make_shared<SlaveDriverProxy>()),
      m_storage(storage),
      m_log(Handleton<Logger>::GetInstance())
{
    m_log->Log("SlaveGateway",
                      __FILE__,
                      __LINE__,
                      false,
                      Logger::LogLevel::INFO);
    if (m_slaveDriver->GetRequestFD() == -1)
    {
        m_log->Log("m_slaveDriver->GetRequestFD() failed", __FILE__, __LINE__);
        throw SlaveDriverError("m_slaveDriver->GetRequestFD() failed");
    }
    
    SetFD(m_slaveDriver->GetRequestFD());
    m_log->Log("after setFD",
                      __FILE__,
                      __LINE__,
                      false,
                      Logger::LogLevel::INFO);
}

SlaveGateway::~SlaveGateway()
{
    Stop();
}

void SlaveGateway::Stop()
{
    m_log->Log("Slave gateway stopped",
                __FILE__,
                __LINE__,
                false,
                Logger::LogLevel::INFO);
    m_slaveDriver->Disconnect();
}

std::pair<DriverData::ActionType,
          std::shared_ptr<TaskArgs>> SlaveGateway::Read()
{
    m_log->Log("Slave gateway read",
                __FILE__,
                __LINE__,
                false,
                Logger::LogLevel::INFO);
    
    std::pair<DriverData::ActionType, std::shared_ptr<TaskArgs>> reqData;

    reqData.second = std::shared_ptr<TaskArgs>(new TaskArgs);
    reqData.second->driver = m_slaveDriver;
    reqData.second->priority = RequestEngineTask::TaskPriority::MEDIUM;
    reqData.second->storage = m_storage;
    reqData.second->driverData = m_slaveDriver->ReceiveRequest();

    reqData.first = reqData.second->driverData->m_type;

    return (reqData);
}

void SlaveGateway::Write(std::pair<DriverData::ActionType,
                         std::shared_ptr<TaskArgs>> replyData)
{
    m_log->Log("Slave gateway write",
                __FILE__,
                __LINE__,
                false,
                Logger::LogLevel::INFO);

    replyData.second->driver->SendReply(replyData.second->driverData);
}

} // namespace hrd14