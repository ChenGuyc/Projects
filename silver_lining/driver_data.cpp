/***********************************
 * file name: driver_data.cpp      *
 * developer: Guy Chen             *
 * date: 30.11.20                  *
 * version 0.1                     *
 ***********************************/

#include "driver_data.hpp"

namespace hrd14
{

DriverData::DriverData(size_t len) : m_len(len), m_buffer(m_len, 0)
{}


} // namespace hrd14