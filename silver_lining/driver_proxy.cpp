/***********************************
 * file name: driver_proxy.cpp     *
 * developer: Guy Chen             *
 * date: 30.11.20                  *
 * version 0.1                     *
 ***********************************/

#include "driver_proxy.hpp"

namespace hrd14
{

DriverProxy::DriverProxy()
{}


DriverError::DriverError(const std::string& errMsg) : runtime_error(errMsg)
{}


} // namespace hrd14