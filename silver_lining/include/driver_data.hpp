/* As part of the Silver Lining project, which allows smart enterprise cloud, 
utilizing existing free storage in organization computers, this class
handles reply and request data

version - 0.1
*/

//Date: Nov. 30, 2020

#ifndef ILRD_HRD14_DRIVER_DATA_HPP
#define ILRD_HRD14_DRIVER_DATA_HPP

#include <cstddef>  // size_t
#include <vector>   // vector

namespace hrd14 
{

static const int HANDLE_SIZE = 8;

struct DriverData
{
    enum ActionType
    {
        READ = 0,
        WRITE,
        DISCONNECT,
        FLUSH,
        TRIM
    };
 
    DriverData(size_t len);
    ~DriverData() = default;

    char m_externalID[HANDLE_SIZE]; 
    int m_internalID;
    
    ActionType m_type;
    size_t m_from;
    size_t m_len;  
  
    int m_status;

    std::vector<char> m_buffer;
};

} //namespace hrd14


#endif //ILRD_HRD14_DRIVER_DATA_HPP