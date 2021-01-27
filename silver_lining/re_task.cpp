/***********************************
 * file name: re_task.cpp          *
 * developer: Guy Chen             *
 * date: 30.11.20                  *
 * version 0.1                     *
 ***********************************/

#include "re_task.hpp"

namespace hrd14
{

RequestEngineTask::RequestEngineTask(TaskPriority priority) 
    : TPTask(static_cast<TPTask::Priority> (priority))
{}

void RequestEngineTask::Execute()
{}

} // namespace hrd14