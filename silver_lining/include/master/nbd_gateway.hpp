
#ifndef NBD_GATEWAY_HPP
#define NBD_GATEWAY_HPP


#include "re_gateway.hpp"
#include "sl_tasks.hpp"
#include "nbd_driver_proxy.hpp"

namespace hrd14
{

class NBDGateway : public RequestEngineGateway<DriverData::ActionType, std::shared_ptr<TaskArgs>>
{
public:
    explicit NBDGateway(std::shared_ptr<DriverProxy> nbdDriver,         
                        std::shared_ptr<Storage> storage);

    NBDGateway(const NBDGateway&)= default;
    NBDGateway& operator=(const NBDGateway&) = default;
    ~NBDGateway() = default;
    
    std::pair<DriverData::ActionType, std::shared_ptr<TaskArgs>> Read() override;
private:

    std::shared_ptr<DriverProxy> m_driver;
    std::shared_ptr<Storage> m_storage;
};

}//namespace hrd14

#endif //NBD_GATEWAY_HPP