/* As part of the Silver Lining project, which allows smart enterprise cloud, 
utilizing existing free storage in organization computers, this class
is an API for storage device in slave.

version - 0.1
*/

//Date: 28.12.20

#ifndef ILRD_HRD14_FILE_STORAGE_HPP
#define ILRD_HRD14_FILE_STORAGE_HPP

#include "storage.hpp"
#include "logger.hpp"
namespace hrd14 
{

class FileStorage : public Storage 
{
public:

    explicit FileStorage(size_t size);
    virtual ~FileStorage();
    
    Status Read(std::shared_ptr<DriverData>) override;
	Status Write(std::shared_ptr<DriverData>) override;

private:	
    size_t m_size;
    int m_fileFD;
    char* m_buffer;
    Logger* m_log;
};
    
} //namespace hrd14


#endif //ILRD_HRD14_FILE_STORAGE_HPP