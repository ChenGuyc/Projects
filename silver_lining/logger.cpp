/***********************************
 * file name: logger.cpp           *
 * developer: Guy Chen             *
 * date: 09.12.20                  *
 * version 0.1                     *
 ***********************************/

#include <thread>   // std::thread::id
#include <iostream> //std::cout
#include <iomanip>  // std::setw
#include "logger.hpp"

namespace hrd14
{

Logger::Logger(const std::string& logFile) : m_level(ERROR)
{
    m_fileHandle.open(logFile);
    if (m_fileHandle.fail())
    {
        throw std::iostream::failure("Cannot open file " + logFile);
    }
    m_fileHandle << "Date and time" << std::setw(13) << "|" <<
                     "thread id" << std::setw(8) << "|" <<
                     "level"<<std::setw(2) << "|" <<
                     "line" << std::setw(2) << "|" <<
                     "fileName"<< std::setw(16) << "|" <<
                     "msg" << std::endl;
    
}

Logger::~Logger()
{
    m_fileHandle.close();
}

void Logger::SetLogLevel(LogLevel level)
{
    m_level = level;
}

void Logger::Log(std::string msg,
             const char* fileName,
             int line, 
             bool printToScreen,
             LogLevel level)
{
    
    ScopeLock<std::mutex> lock(m_mutex);

    std::time_t now = std::chrono::system_clock::to_time_t(
                            std::chrono::system_clock::now());
    
    std::string timestamp = std::ctime(&now);
    std::string fileNameStr(fileName);

    std::thread::id this_id = std::this_thread::get_id();
    int num = 4;
    if (99 < line)
    {
        num = 3;
    }

    fileNameStr = fileNameStr.substr(fileNameStr.find_last_of("/") + 1);
    
    m_fileHandle << timestamp.substr(0, timestamp.length() -1) <<
                    std::setw(2) << "|" << this_id <<
                    std::setw(2) << "|" << level <<
                    std::setw(6) << "|" << line <<
                    std::setw(num) << "|" <<
                    fileNameStr <<
                    std::setw(24 - fileNameStr.length()) << "|" << msg << std::endl;

    if(printToScreen)
    {
        std::cout << timestamp.substr(0, timestamp.length() -1) <<
                        std::setw(2) << "|" << this_id <<
                    std::setw(2) << "|" << level <<
                    std::setw(6) << "|" << line <<
                    std::setw(num) << "|" << 
                    fileNameStr <<
                    std::setw(24 - fileNameStr.length()) << "|" << msg << std::endl;
    }
    
}

}//hrd14