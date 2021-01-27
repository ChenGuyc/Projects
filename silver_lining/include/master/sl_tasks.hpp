
#ifndef ILRD_HRD14_TASK_HPP
#define ILRD_HRD14_TASK_HPP

#include "storage.hpp"
#include "driver_proxy.hpp"
#include "driver_data.hpp"
#include "re_task.hpp"

namespace hrd14
{

class TaskArgs
{
public:
    std::shared_ptr<DriverProxy> driver;
    std::shared_ptr<DriverData> driverData;
    std::shared_ptr<Storage> storage;
    RequestEngineTask::TaskPriority priority;
};

/*************/

class Read: public RequestEngineTask
{
public:
    ~Read() = default;
    static std::shared_ptr<RequestEngineTask> Create(std::shared_ptr<TaskArgs> args);

    Read(const Read&) = delete;
    Read& operator=(const Read&) = delete;
private:
    Read(std::shared_ptr<TaskArgs> args);
    void Execute() override;
    
    std::shared_ptr<TaskArgs> m_args;
};

/*************/

class Write: public RequestEngineTask
{
public:
    ~Write() = default;
    static std::shared_ptr<RequestEngineTask> Create(std::shared_ptr<TaskArgs> m_args);

    Write(const Write&) = delete;
    Write& operator=(const Write&) = delete;
private:
    Write(std::shared_ptr<TaskArgs> args);
    void Execute() override;

    std::shared_ptr<TaskArgs> m_args;

};

/*************/

class Disconnect: public RequestEngineTask
{
public:
    ~Disconnect() = default;
    static std::shared_ptr<RequestEngineTask> Create(std::shared_ptr<TaskArgs> args);

    Disconnect(const Disconnect&) = delete;
    Disconnect& operator=(const Disconnect&) = delete;
private:
    Disconnect(std::shared_ptr<TaskArgs> args);
    void Execute() override;

    std::shared_ptr<TaskArgs> m_args;
};

/*************/

class Flush: public RequestEngineTask
{
public:
    ~Flush() = default;
    static std::shared_ptr<RequestEngineTask> Create(std::shared_ptr<TaskArgs> args);

    Flush(const Flush&) = delete;
    Flush& operator=(const Flush&) = delete;
private:
    Flush(std::shared_ptr<TaskArgs> args);
    void Execute() override;

    std::shared_ptr<TaskArgs> m_args;
};

/*************/

class Trim: public RequestEngineTask
{
public:
    ~Trim() = default;
    static std::shared_ptr<RequestEngineTask> Create(std::shared_ptr<TaskArgs> args);

    Trim(const Trim&) = delete;
    Trim& operator=(const Trim&) = delete;
private:
    Trim(std::shared_ptr<TaskArgs> args);
    void Execute() override;

    std::shared_ptr<TaskArgs>m_args;
};


}//hrd14

#endif // ILRD_HRD14_TASK_HPP