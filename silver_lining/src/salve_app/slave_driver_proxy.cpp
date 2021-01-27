/*****************************************
 * file name: slave_driver_proxy.cpp     *
 * developer: Guy Chen                   *
 * date: 06.01.21                        *
 * version 0.1                           *
 *****************************************/

#include <csignal>      // sigfillset, sigprocmask

#include <sys/types.h>  // socketpair, open
#include <sys/socket.h> // socket
#include <unistd.h>     // read
#include <cstring>      // memcpy
#include <sys/stat.h>   // open
#include <fcntl.h>      // open
#include <algorithm>    // std::copy
#include "slave_driver_proxy.hpp"
#include "utils.hpp"

namespace hrd14
{

static const ssize_t ERROR = -1;
static const size_t BLOCK_SIZE = 4094;
static const size_t MSG_SIZE = 4136;
static const size_t MAX_HEADER_SIZE = 40;
static const int PORT = 1111;
/*******************************/

SlaveDriverProxy::SlaveDriverProxy() 
                  : m_log(Handleton<Logger>::GetInstance()), 
                    m_requestFD(socket(AF_INET, SOCK_DGRAM, 0)),
                    m_parsing(std::make_shared<TextProtocolParsing>(MSG_SIZE)),
                    m_isConnected(true)
{
    m_log->Log("create slave driver proxy",
               __FILE__,
               __LINE__,
               true,
               Logger::LogLevel::INFO);
    
    if (m_requestFD < 0)
    {
        m_log->Log("socket failed", __FILE__, __LINE__);
        throw SlaveDriverError("socket failed");
    }

    memset(&m_servAddr, 0, sizeof(m_servAddr));
    m_servAddr.sin_family = AF_INET; 
    m_servAddr.sin_port = htons(PORT); 
    m_servAddr.sin_addr.s_addr = INADDR_ANY;

    m_log->Log("after set m_servAddr",
               __FILE__,
               __LINE__,
               true,
               Logger::LogLevel::INFO);

    const char* start = "Hi Master I am your slave";
    
    if (0 > sendto(m_requestFD,
                   start,
                   strlen(start), 
                   MSG_CONFIRM,
                   reinterpret_cast<const struct sockaddr *>(&m_servAddr),
                   sizeof(m_servAddr)))
    {
        m_log->Log("send feply failed", __FILE__, __LINE__);
        throw SlaveDriverError("send feply failed");
    }
}
/*******************************/
SlaveDriverProxy::~SlaveDriverProxy()
{ 
    Disconnect();
}

/*******************************/

std::shared_ptr<DriverData> SlaveDriverProxy::ReceiveRequest()
{
    char buffer[MSG_SIZE];
    socklen_t len = MSG_SIZE;

    m_log->Log("ReceiveRequest",
               __FILE__,
               __LINE__,
               true,
               Logger::LogLevel::INFO);

    recvfrom(m_requestFD,
             buffer,
             MSG_SIZE,
             MSG_WAITALL,
             reinterpret_cast<struct sockaddr *>(&m_servAddr),
             &len);
    
    // deserialization
    auto data = m_parsing->Deserialization(buffer);

    return(data);
}
/*******************************/
void SlaveDriverProxy::SendReply(std::shared_ptr<DriverData> reply)
{
    // serialization 
    char buffer[MSG_SIZE];

    ScopeLock<std::mutex> lock(m_mutex);

    m_parsing->Serialization(buffer, reply);
    if (0 > sendto(m_requestFD,
           buffer,
           MSG_SIZE, 
           MSG_CONFIRM,
           reinterpret_cast<const struct sockaddr *>(&m_servAddr),
           sizeof(m_servAddr)))
    {
        m_log->Log("send feply failed", __FILE__, __LINE__);
        throw SlaveDriverError("send feply failed");
    }
}
/*******************************/
void SlaveDriverProxy::Disconnect()
{
    // close socket
    if (m_isConnected)
    {
        m_isConnected = false;
        if (ERROR == close(m_requestFD))
        {
            m_log->Log("close failed", __FILE__, __LINE__);
            throw SlaveDriverError("close failed");
        }   
    }
}

/*******************************/
int SlaveDriverProxy::GetRequestFD() const
{
    return (m_requestFD);
}


/*******************************/
SlaveDriverError::SlaveDriverError(const std::string& errMsg)
    : DriverError(errMsg)
{}

} // namespace hrd14