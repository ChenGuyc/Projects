
/* 
 *  The logger will be used as a Handleton, hence, the logger will be created 
 *  only  once for the program
 *  All the logs will be saved in the same log file.
 *  Log method is synchronous
 *  The data in the log file will have info of:
        (1) Date + time
        (2) Thread ID
        (3) Log Level 
        (4) message
        (5) File name
        (6) Line number
 *  level arg in Log function will determine the specific log entry level and
 *  will not change log-level for the entire program. In case of a collision 
 *  between the 2 values, higher level prevails
 * 
 *  SetLogLevel is meant to change log level for the entire program, as the new 
 *  default

    version - 0.1 waiting for mentor approval
    Date: Dec, 9 2020
 */


#ifndef ILRD_HRD14_LOGGER_HPP
#define ILRD_HRD14_LOGGER_HPP

#include <fstream>  // std::ofstream

#include "handleton.hpp"

namespace hrd14
{

class Logger
{

public:
    enum LogLevel
    {
        ERROR = 0,
        INFO,
        DEBUG_LEVEL
    };
    Logger(const Logger* other) = delete;
    Logger& operator=(const Logger& other) = delete;
    ~Logger();

    void Log(std::string msg,
             const char* fileName,
             int line, 
             bool printToScreen = false,
             LogLevel level = ERROR);

    void SetLogLevel(LogLevel level);

private:
    Logger(const std::string& logFile = "../../log/log.txt");

    friend class Handleton<Logger>;
    LogLevel m_level;
    std::ofstream m_fileHandle;
    std::mutex m_mutex;
};

}//namespace hrd14

#endif //ILRD_HRD14_LOGGER_HPP