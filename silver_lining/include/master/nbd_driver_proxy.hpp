/* NBD driver proxy inherits the driver_proxy API
as part of Silver Lining project

version - 0.1
        - 0.11 add utility functions (OpenDev, ClearDev, WaitOnRequest, IOCtl)
                
*/

//Date: Nov. 30, 2020

#ifndef ILRD_HRD14_NBD_DRIVER_PROXY_HPP
#define ILRD_HRD14_NBD_DRIVER_PROXY_HPP

#include <thread>

#include "driver_proxy.hpp"
#include "logger.hpp"

namespace hrd14 
{

class NBDDriverProxy : public DriverProxy
{
    
public:
    explicit NBDDriverProxy(const std::string& devFile,
                            size_t storageSize);
    explicit NBDDriverProxy(const std::string& devFile,
                            size_t blockSize,
                            size_t numBlocks);
    
    ~NBDDriverProxy() override;
    
    std::shared_ptr<DriverData> ReceiveRequest() override;
    void SendReply(std::shared_ptr<DriverData>) override;
    
    void Disconnect() override;
    int GetRequestFD() const override;
    
private:
    int m_requestFD;
    int m_nbdFD;
    std::thread m_nbdThread;
    int m_nbdDev;
    bool m_isConeccted;
    Logger* m_log;

    std::mutex m_mutex;
    //members? utility functions
    int OpenDev(const std::string& devFile);
    void ClearDev();
    void WaitOnRequest(); // thread function
    template<typename... Requests>
    void IOCtl(const char* errMsg, Requests... requests);
    
};

class NBDDriverError : public DriverError
{
public:
    explicit NBDDriverError(const std::string& errMsg);
    virtual ~NBDDriverError() = default;
};

} //namespace hrd14


#endif //ILRD_HRD14_NBD_DRIVER_PROXY_HPP