/************************
 * ram_storage.cpp      *
 *                      *
 * developer Hen        *
 * reviewer ****        *
 * date 30.11.20        *
 * version 0.1          *
 ***********************/

#include <cstring>
#include "ram_storage.hpp"
namespace hrd14
{

RAMStorage::RAMStorage(size_t size) : Storage(size), m_buffer(size, 0)
{}

Storage::Status RAMStorage::Read(std::shared_ptr<DriverData> data)
{

    std::copy(m_buffer.data() + data->m_from, 
              m_buffer.data() + data->m_from + data->m_len,
              data->m_buffer.data());

    return (SUCCESS);
}

Storage::Status RAMStorage::Write(std::shared_ptr<DriverData> data)
{
    // write to storage
    std::copy(data->m_buffer.data(), 
              data->m_buffer.data() + data->m_len,
              m_buffer.data() + data->m_from);
    
    return (SUCCESS);
}

} // namespace hrd14