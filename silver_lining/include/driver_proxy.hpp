/* 
As part of the Silver Lining project, which allows smart enterprise cloud, 
utilizing existing free storage in organization computers, this class
is an abstract API for main operations.
It's designed to support NBD module or any other module that
will be used in the future and inherit from this API

version - 0.1
*/

//Date: Nov. 30, 2020

#ifndef ILRD_HRD14_DRIVER_PROXY_HPP
#define ILRD_HRD14_DRIVER_PROXY_HPP

#include <memory>       // shared_pointer


#include "driver_data.hpp"

namespace hrd14 
{

class DriverProxy 
{
public:
    explicit DriverProxy();
    virtual ~DriverProxy() = default;

    DriverProxy(const DriverProxy& other) = delete;
    DriverProxy& operator=(const DriverProxy& other) = delete;
    
    virtual std::shared_ptr<DriverData> ReceiveRequest() = 0;
    virtual void SendReply(std::shared_ptr<DriverData>) = 0;
    
    virtual void Disconnect() = 0;
    virtual int GetRequestFD() const = 0; 
};


/* 
 *  Driver Error may thows an exception from 
 * 
 * 
 * version    date    comments
 * 0.1        
 * 
 */


//Date: Nov. 30, 2020

class DriverError : public std::runtime_error
{
public:
    explicit DriverError(const std::string& err_msg);
    virtual ~DriverError() = default;
};

} //namespace hrd14


#endif //ILRD_HRD14_DRIVER_PROXY_HPP