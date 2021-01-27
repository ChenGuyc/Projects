/* As part of the Silver Lining project, which allows smart enterprise cloud, 
utilizing existing free storage in organization computers, this class
is an abstract API for various storage devices.
It's designed to support RAM storage or others

version - 0.1
          0.12  modified Read, Write return type 14.12.20
*/

//Date: Nov. 30, 2020

#ifndef ILRD_HRD14_STORAGE_HPP
#define ILRD_HRD14_STORAGE_HPP

#include <cstddef>  // size_t
#include <memory>   // shared_ptr

#include "driver_data.hpp"

namespace hrd14 
{

class Storage 
{
public:
    enum Status
    {
        SUCCESS = 0,
        FAIL,
        BKP
    };

    explicit Storage(size_t size);
    
    virtual ~Storage() = default;
    
    Storage(const Storage& other) = delete;
    Storage& operator=(const Storage& other) = delete;
    
    virtual Status Read(std::shared_ptr<DriverData>) = 0;
	virtual Status Write(std::shared_ptr<DriverData>) = 0;

private:
    size_t m_size;
};
    
} //namespace hrd14


#endif //ILRD_HRD14_STORAGE_HPP