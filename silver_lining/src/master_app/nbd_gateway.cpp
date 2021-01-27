
/***********************************
 * file name: nbd_gateway.cpp      *
 * developer: Guy Chen             *
 * date: 30.11.20                  *
 * version 0.1                     *
 ***********************************/

#include "nbd_gateway.hpp"

namespace hrd14
{

NBDGateway::NBDGateway(std::shared_ptr<DriverProxy> nbdDriver, 
                       std::shared_ptr<Storage> storage)
    : m_driver(nbdDriver),
      m_storage(storage)
{
    SetFD(m_driver->GetRequestFD());
}


std::pair<DriverData::ActionType, std::shared_ptr<TaskArgs>> NBDGateway::Read()
{
    std::pair<DriverData::ActionType, std::shared_ptr<TaskArgs>> pair;

    pair.second = std::shared_ptr<TaskArgs>(new TaskArgs);
    pair.second->driver = m_driver;
    pair.second->priority = RequestEngineTask::TaskPriority::MEDIUM;
    pair.second->storage = m_storage;
    pair.second->driverData = m_driver->ReceiveRequest();

    pair.first = pair.second->driverData->m_type;

    return (pair);
}

} // namespace hrd14