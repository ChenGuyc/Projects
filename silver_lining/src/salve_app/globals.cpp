/***********************************
 * file name: globals.cpp          *
 * developer: Guy Chen             *
 * date: 28.12.20                  *
 * version 0.1                     *
 ***********************************/


#include <memory>
#include "handleton.hpp"
#include "logger.hpp"
#include "factory.hpp"
#include "re_task.hpp"
#include "driver_data.hpp"
#include "slave_tasks.hpp"

namespace hrd14
{
    
INIT_HANDLETON(Logger)

using Factory_t = Factory< RequestEngineTask,
                          DriverData::ActionType,
                          std::shared_ptr<TaskArgs> >;
INIT_HANDLETON(Factory_t)

}//hrd14