
#ifndef SLAVE_GATEWAY_HPP
#define SLAVE_GATEWAY_HPP

#include "re_gateway.hpp"
#include "slave_tasks.hpp"
#include "slave_driver_proxy.hpp"
#include "handleton.hpp"

namespace hrd14
{
class SlaveGateway : public RequestEngineGateway<DriverData::ActionType,    
                                                 std::shared_ptr<TaskArgs>>
{
public:
    explicit SlaveGateway(std::shared_ptr<Storage> storage);

    SlaveGateway(const SlaveGateway&)= default;
    SlaveGateway& operator=(const SlaveGateway&) = default;
    ~SlaveGateway();

    std::pair<DriverData::ActionType, std::shared_ptr<TaskArgs>> Read() 
    override;
    
    void Stop() override;
    void Write(std::pair<DriverData::ActionType,
               std::shared_ptr<TaskArgs>>);
    
private:

    std::shared_ptr<DriverProxy> m_slaveDriver;
    std::shared_ptr<Storage> m_storage;
    Logger* m_log;
};

}//namespace hrd14

#endif //SLAVE_GATEWAY_HPP