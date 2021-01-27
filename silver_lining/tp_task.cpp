/***********************************
 * file name: tp_task.cpp          *
 * developer: Guy Chen             *
 * date: 14.12.20                  *
 * version 0.1                     *
 ***********************************/

#include <memory>   //std::shared_ptr

#include "tp_task.hpp"


namespace hrd14
{

TPTask::TPTask(Priority priority): m_priority(priority)
{}

bool operator<(const std::shared_ptr<TPTask>& lhs,
            const std::shared_ptr<TPTask>& rhs)
{
    return (lhs->m_priority < rhs->m_priority);
}

}//hrd14
