/***********************************
 * file name: file_storage.cpp     *
 * developer: Guy Chen             *
 * date: 28.12.20                  *
 * version 0.1                     *
 ***********************************/

#include <cstring>      // memcoy
#include <sys/types.h>  // open
#include <sys/stat.h>   // open
#include <fcntl.h>      // open
#include <unistd.h>     // close
#include <sys/mman.h>   // mmap

#include <iostream>

#include "file_storage.hpp"

namespace hrd14
{

FileStorage::FileStorage(size_t size) :
            Storage(size),
            m_size(size),
            m_fileFD(open("./test/test.txt", O_CREAT | O_RDWR)),
            m_buffer(static_cast<char*>(mmap(NULL, m_size, PROT_WRITE,
                                                  MAP_SHARED,
                                                  m_fileFD, 0))),
            m_log(Handleton<Logger>::GetInstance())
{
    m_log->Log("open file storage",
               __FILE__,
               __LINE__,
               false,
               Logger::LogLevel::INFO);
    
    if (-1 == m_fileFD)
    {
        m_log->Log("open file storage failed", __FILE__, __LINE__);
        throw std::runtime_error("open file storage failed");
    }

    if (ftruncate(m_fileFD, m_size))
    {
        m_log->Log("file storage allocation failed", __FILE__, __LINE__);
        throw std::runtime_error("file storage allocation failed");
    }

    m_log->Log("allocate file storage",
               __FILE__,
               __LINE__,
               false,
               Logger::LogLevel::INFO);
}

FileStorage::~FileStorage()
{
    close(m_fileFD);
}

Storage::Status FileStorage::Read(std::shared_ptr<DriverData> data)
{
    if (data->m_from <= m_size)
    {
        memcpy(data->m_buffer.data(), m_buffer + data->m_from, data->m_len);

        m_log->Log("Read from \"real\" storage",
                   __FILE__, __LINE__, false,
                   Logger::LogLevel::INFO);;
    }
    else
    {
        m_log->Log("Read from \"backup\" storage",
                   __FILE__, __LINE__, false,
                   Logger::LogLevel::INFO);

        memcpy(data->m_buffer.data(),
                m_buffer + m_size / 2 + data->m_from, data->m_len);
    }
    return (SUCCESS);
}

Storage::Status FileStorage::Write(std::shared_ptr<DriverData> data)
{
    if (data->m_from <= m_size)
    {
        m_log->Log("write to \"real\" storage",
                   __FILE__, __LINE__, false,
                   Logger::LogLevel::INFO);

        memcpy(m_buffer + data->m_from,
                data->m_buffer.data() + data->m_len, data->m_len);
    }
    else
    {
        m_log->Log("write to \"backup\" storage",
                   __FILE__,
                   __LINE__,
                   false,
                   Logger::LogLevel::INFO);
        memcpy(m_buffer + (data->m_from + m_size / 2) + data->m_from,
                data->m_buffer.data() + data->m_len, data->m_len);
        
        return (BKP);
    }

    return (SUCCESS);
}

} // namespace hrd14