/***************************************
 * file name: nbd_driver_proxy.cpp     *
 * developer: Guy Chen                 *
 * date: 30.11.20                      *
 * version 0.1                         *
 ***************************************/

#include <sys/ioctl.h>  // ioctl
#include <linux/nbd.h>  // define, struct nbd_request, struct nbd_reply
#include <csignal>      // sigfillset, sigprocmask

#include <sys/types.h>  // socketpair, open
#include <sys/socket.h> // socketpair
#include <iostream>     // cerr
#include <sys/stat.h>   // open
#include <fcntl.h>      // open
#include <thread>       // thread
#include <unistd.h>     // read
#include <cstring>     // memcpy

#include "nbd_driver_proxy.hpp"
#include "utils.hpp"

namespace hrd14
{

static const size_t FIRST = 0;
static const size_t LAST = 8;

static void BlockSignals();
static void CopyRequest(std::shared_ptr<DriverData> request,
                        struct nbd_request& nbdRequest);
static void CopyReply(struct nbd_reply& nbdReply,
                      std::shared_ptr<DriverData> reply);
static const ssize_t ERROR = -1;
/*******************************/
NBDDriverProxy::NBDDriverProxy(const std::string& devFile, size_t storageSize) : m_isConeccted(true), m_log(Handleton<Logger>::GetInstance())
{
    m_nbdDev = OpenDev(devFile);

    IOCtl("ioctl set size", NBD_SET_SIZE, storageSize);
    IOCtl("ioctl clear socket", NBD_CLEAR_SOCK, m_nbdFD);
    
    m_nbdThread = std::thread(&NBDDriverProxy::WaitOnRequest, this);
}

/*******************************/

NBDDriverProxy::NBDDriverProxy(const std::string& devFile,
                               size_t blockSize,
                               size_t numBlocks)
    : NBDDriverProxy(devFile, blockSize * numBlocks)
{}

/*******************************/
NBDDriverProxy::~NBDDriverProxy()
{
    // disconnector
    if (m_isConeccted)
    {
        Disconnect();
    }
}
/*******************************/
std::shared_ptr<DriverData> NBDDriverProxy::ReceiveRequest()
{
    struct nbd_request nbdRequest;

    if (ERROR == read(m_requestFD, &nbdRequest, sizeof(nbdRequest)))
    {
        m_log->Log("read failed", __FILE__, __LINE__);
        throw NBDDriverError("read failed");
    }

    auto data = std::make_shared<DriverData>(ntohl(nbdRequest.len));

    CopyRequest(data, nbdRequest);

    if (nbdRequest.magic != htonl(NBD_REQUEST_MAGIC))
    {
        m_log->Log("wrong magic number", __FILE__, __LINE__);
        throw NBDDriverError("wrong magic number");    
    }

    if (data->m_type == DriverData::ActionType::WRITE)
    {   
        ReadAll(m_requestFD, &data->m_buffer.at(0), data->m_len);
    }

    return (data);
}
/*******************************/
void NBDDriverProxy::SendReply(std::shared_ptr<DriverData> reply)
{
    struct nbd_reply nbdReply;
    nbdReply.magic = htonl(NBD_REPLY_MAGIC);

    CopyReply(nbdReply, reply);

    ScopeLock<std::mutex> lock(m_mutex);

    WriteAll(m_requestFD, reinterpret_cast<char*>(&nbdReply), sizeof(nbdReply));

    if (reply->m_type == DriverData::ActionType::READ)
    {
        WriteAll(m_requestFD,
                 reply->m_buffer.data(),
                 reply->m_len);
    }
}
/*******************************/
void NBDDriverProxy::Disconnect()
{
    IOCtl("ioctl Disconnect", NBD_DISCONNECT);
    ClearDev();
    
    m_nbdThread.join();
    
    m_isConeccted = false;
    close(m_nbdFD);
    close(m_requestFD);
    close(m_nbdDev);

    
}

/*******************************/
int NBDDriverProxy::GetRequestFD() const
{
    return (m_requestFD);
}
/*******************************/
int NBDDriverProxy::OpenDev(const std::string& devFile)
{
    int sp[2];
    if (-1 == socketpair(AF_UNIX, SOCK_STREAM, 0, sp))
    {
        m_log->Log("socketpair failed", __FILE__, __LINE__, true);
        throw NBDDriverError("socketpair failed");
    }

    m_requestFD = sp[0];
    m_nbdFD = sp[1];
    
    int nbd = open(devFile.c_str(), O_RDWR);
    if (-1 == nbd)
    {   
        m_log->Log("open failed", __FILE__, __LINE__, true);
        throw NBDDriverError("open failed");
    }

    return (nbd);
}

/*******************************/
void NBDDriverProxy::ClearDev()
{
    IOCtl("ioctl clear queue", NBD_CLEAR_QUE);
    IOCtl("ioctl clear socket", NBD_CLEAR_SOCK);
}

/*******************************/

template<typename... Requests>
void NBDDriverProxy::IOCtl(const char* errMsg, Requests... requests)
{
     if (-1 == ioctl(m_nbdDev, requests...))
    {
        m_log->Log(errMsg, __FILE__, __LINE__, true);
        throw NBDDriverError(errMsg);
    }
}

/*******************************/

void NBDDriverProxy::WaitOnRequest()
{
    try
    {
        BlockSignals();

        IOCtl("ioctl set socket", NBD_SET_SOCK, m_nbdFD);

        #if defined NBD_SET_FLAGS
        int flags = 0;
        
        #if defined NBD_FLAG_SEND_TRIM
            flags |= NBD_FLAG_SEND_TRIM;
        #endif // NBD_FLAG_SEND_TRIM

        #if defined NBD_FLAG_SEND_FLUSH
            flags |= NBD_FLAG_SEND_FLUSH;
        #endif // NBD_FLAG_SEND_FLUSH
        
        IOCtl("ioctl set flags", NBD_SET_FLAGS, flags);
        #endif // NBD_SET_FLAGS

        IOCtl("ioctl do it", NBD_DO_IT);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        Disconnect();
    }
}

/*******************************/

static void BlockSignals()
{
    sigset_t sigset;
    if (0 != sigfillset(&sigset) ||
        0 != pthread_sigmask(SIG_SETMASK, &sigset, NULL))
    {  
        throw NBDDriverError("block signals faild");
    }
}

/*******************************/
static void CopyRequest(std::shared_ptr<DriverData> request,
                        struct nbd_request& nbdRequest)
{
   
    request->m_from = ntohll(nbdRequest.from);
    
    // convertion Big to little 
    request->m_type = static_cast<DriverData::ActionType>(ntohl(nbdRequest.type));
    
    std::copy(&nbdRequest.handle[FIRST],
              &nbdRequest.handle[LAST],
              &request->m_externalID[FIRST]);
}
/*******************************/
static void CopyReply(struct nbd_reply& nbdReply,
                      std::shared_ptr<DriverData> reply)
{
    nbdReply.error = htonl(reply->m_status);

    std::copy(&reply->m_externalID[FIRST],
             &reply->m_externalID[LAST],
             &nbdReply.handle[FIRST]);
}
/*******************************/
NBDDriverError::NBDDriverError(const std::string& errMsg)
    : DriverError(errMsg)
{}

} // namespace hrd14