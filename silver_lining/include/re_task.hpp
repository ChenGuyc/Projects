/*
* A generic, abstract Task class
* Each new task should receive it's priority upon creation
* Tasks inheriting from this abstract class must override the virtual Execute function.
* Version         Date        Comments
* 0.1             23.12.20     API mentor approved
*/


#ifndef ILRD_HRD14_RETASK_HPP
#define ILRD_HRD14_RETASK_HPP

#include "tp_task.hpp"

namespace hrd14
{

class RequestEngineTask : public TPTask
{
public:
    enum class TaskPriority
    {
        LOW = TPTask::Priority::LOW,
        MEDIUM = TPTask::Priority::MEDIUM,
        HIGH = TPTask::Priority::HIGH
    };

    explicit RequestEngineTask(TaskPriority priority = TaskPriority::MEDIUM);
    RequestEngineTask(const RequestEngineTask&)= default;
    RequestEngineTask& operator=(const RequestEngineTask&) = default;
    ~RequestEngineTask() = default;
private:
    virtual void Execute() = 0;
};

}//namespace hrd14

#endif //ILRD_HRD14_RETASK_HPP