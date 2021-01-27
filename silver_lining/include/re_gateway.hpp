/*
* A generic, abstract template class
* Request engine gateway reads the incoming requests and returns Key and Args 
* This class holds the file descriptor and provides a "getter" to its value 
* 
* Version         Date        Comments
* 0.1             23.12.20    API mentor approved
* 0.2             27.12.20    Ctor modified
*/

#ifndef ILRD_HRD14_REGATEWAY_HPP
#define ILRD_HRD14_REGATEWAY_HPP

#include <utility>

namespace hrd14
{

template <typename Key, typename Args>
class RequestEngineGateway
{
public:
    explicit RequestEngineGateway() = default;
    RequestEngineGateway(const RequestEngineGateway&)= default;
    RequestEngineGateway& operator=(const RequestEngineGateway&) = default;
    ~RequestEngineGateway() = default;

    virtual std::pair<Key, Args> Read() = 0;
    virtual void Stop() = 0;
    void SetFD(int fd);
    int GetFD() const;

private:
    int m_fd;
};

template <typename Key, typename Args>
void RequestEngineGateway<Key, Args>::SetFD(int fd)
{
    m_fd = fd;
}

template <typename Key, typename Args>
int RequestEngineGateway<Key, Args>::GetFD() const
{
    return (m_fd);
}

}//namespace hrd14

#endif //ILRD_HRD14_REGATEWAY_HPP