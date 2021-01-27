/* As part of the Silver Lining project, which allows smart enterprise cloud, 
utilizing existing free storage in organization computers, this class
is an API for RAM storage device.

version - 0.1
          0.12  modified Read, Write return type 14.12.20
*/

//Date: Nov. 30, 2020

#ifndef ILRD_HRD14_RAM_STORAGE_HPP
#define ILRD_HRD14_RAM_STORAGE_HPP

#include "storage.hpp"

namespace hrd14 
{

class RAMStorage : public Storage 
{
public:
    explicit RAMStorage(size_t size);
    virtual ~RAMStorage() = default;
    
    Status Read(std::shared_ptr<DriverData>) override;
	Status Write(std::shared_ptr<DriverData>) override;
private:	
    std::vector<char> m_buffer;
};
    
} //namespace hrd14


#endif //ILRD_HRD14_RAM_STORAGE_HPP