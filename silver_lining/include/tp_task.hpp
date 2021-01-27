/*
* Abstract Task class
* Implemented with command design pattern 
*/
#ifndef ILRD_HRD14_TPTASK_HPP
#define ILRD_HRD14_TPTASK_HPP

#include <memory>   //std::shared_ptr
namespace hrd14
{
    
class TPTask;
bool operator<(const std::shared_ptr<TPTask>& lhs,
               const std::shared_ptr<TPTask>& rhs);
class TPTask
{

public:
    enum Priority
    {
        LOW = 0,
        MEDIUM,
        HIGH,
        ADMIN
    };

    explicit TPTask(Priority priority);
    virtual ~TPTask() = default;
    TPTask(const TPTask& other) = default;
    TPTask& operator=(const TPTask& other) = default;


private:

    virtual void Execute() = 0;
    Priority m_priority;

    friend bool operator<(const std::shared_ptr<TPTask>& lhs,
                          const std::shared_ptr<TPTask>& rhs);

    friend class ThreadPool;
};
}//namespace hrd14

#endif //ILRD_HRD14_TPTASK_HPP
