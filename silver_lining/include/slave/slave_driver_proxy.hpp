/* slave driver proxy inherits the driver_proxy API
as part of Silver Lining project

version - 0.1
                
*/

//Date: 28.12.20

#ifndef ILRD_HRD14_SLAVE_DRIVER_PROXY_HPP
#define ILRD_HRD14_SLAVE_DRIVER_PROXY_HPP

#include <netinet/in.h> // struct sockaddr_in
#include "driver_proxy.hpp"
#include "logger.hpp"
#include "text_protocol_parsig.hpp"

namespace hrd14 
{

class SlaveDriverProxy : public DriverProxy
{
    
public:
    explicit SlaveDriverProxy();
    
    ~SlaveDriverProxy() override;
    
    std::shared_ptr<DriverData> ReceiveRequest() override;
    void SendReply(std::shared_ptr<DriverData>) override;
    
    void Disconnect() override;
    int GetRequestFD() const override;
    
private:
    std::mutex m_mutex;
    Logger* m_log;
    struct sockaddr_in m_servAddr;
    int m_requestFD;
    std::shared_ptr<Parsing> m_parsing;
    bool m_isConnected;
};

class SlaveDriverError : public DriverError
{
public:
    explicit SlaveDriverError(const std::string& errMsg);
    virtual ~SlaveDriverError() = default;
};

} //namespace hrd14


#endif //ILRD_HRD14_SLAVE_DRIVER_PROXY_HPP