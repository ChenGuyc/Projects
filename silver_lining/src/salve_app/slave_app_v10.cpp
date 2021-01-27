/***********************************
 * file name: slave_app_v10.cpp     *
 * developer: Guy Chen             *
 * date: 09.01.21                  *
 * version 0.1                     *
 ***********************************/

#include "slave_app.hpp"

/*******************************/

using namespace hrd14;

static void StopHandler(int signal);
static void SignalHandler();
static void ConfigTasks();

/*******************************/

Logger* g_logger = Handleton<Logger>::GetInstance();

/*******************************/
RequestEngine<DriverData::ActionType, std::shared_ptr<TaskArgs>> g_reqEngine;

int main(int argc, char const *argv[])
{
    try
    {
        SignalHandler();
        size_t size = atoll(argv[1]) * 1000000 * 2;

        g_logger->Log("Config Gateway",
                      __FILE__,
                      __LINE__,
                      false,
                      Logger::LogLevel::INFO);

        g_reqEngine.ConfigGateway(std::make_shared<SlaveGateway>    
                                 (std::make_shared<FileStorage>(size)));

        ConfigTasks();
        
        g_logger->Log("Start Request Engine",
                      __FILE__,
                      __LINE__,
                      false,
                      Logger::LogLevel::INFO);

        g_reqEngine.Start();
    }
    catch (SlaveDriverError& e)
    {
        g_logger->Log(e.what(),__FILE__,__LINE__);
    }
    catch (DriverError& e)
    {
        g_logger->Log(e.what(),  __FILE__, __LINE__);
    }
    catch (...)
    {
        g_logger->Log("unknown error", __FILE__, __LINE__);
    }

/********************************/

    (void) argc;
    return (0);
}

/*******************t************/
static void SignalHandler()
{
    struct sigaction act;
    act.sa_handler = StopHandler;
    
    act.sa_flags = SA_RESTART;

    sigaction(SIGTERM, &act, 0);
    sigaction(SIGINT, &act, 0);
    
}
/*******************************/

static void StopHandler(int signal)
{
    g_reqEngine.Stop();
    g_logger->Log("in StopHandler",
                  __FILE__,
                  __LINE__,
                  false,
                  Logger::LogLevel::INFO);
    (void)signal;
}

/*******************************/

void ConfigTasks()
{
    g_logger->Log("Config tasks",
                  __FILE__,
                  __LINE__,
                  false,
                  Logger::LogLevel::INFO);

    g_reqEngine.ConfigTask(DriverData::ActionType::READ, Read::Create);

    g_reqEngine.ConfigTask(DriverData::ActionType::WRITE, Write::Create);
}