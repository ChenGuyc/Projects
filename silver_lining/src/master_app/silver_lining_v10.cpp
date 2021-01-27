/****************************************
 * file name: sliver_lining_v10.cpp     *
 * developer: Guy Chen                  *
 * date: 30.11.20                       *
 * version 0.2                          *
 ****************************************/

#include "silver_lining.hpp"
#include "request_engine.hpp"
/*******************************/

using namespace hrd14;

static void DisconnectHandler(int signal);
static void SignalHandler();


static void ConfigTasks();
/*******************************/

std::shared_ptr<DriverProxy> g_driver;

std::shared_ptr<Storage> g_storage;

RequestEngine<DriverData::ActionType, std::shared_ptr<TaskArgs>> g_reqEngine;

Logger* g_logger = Handleton<Logger>::GetInstance();
/*******************************/

int main(int argc, char const *argv[])
{
    SignalHandler();
    size_t size = atoll(argv[2]) * 1000000;

    g_driver = std::make_shared<NBDDriverProxy>(argv[1], size);
    
    g_storage = std::make_shared<RAMStorage>(size);
    
/********************************/
    try 
    {
        ConfigTasks();

        auto nbdGetway = std::make_shared<NBDGateway>(g_driver, g_storage);

        g_reqEngine.ConfigGateway(nbdGetway);

        g_reqEngine.Start();
    }
    catch (NBDDriverError& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (DriverError& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {}

/********************************/

    (void) argc;
    return (0);
}

/*******************t************/
static void SignalHandler()
{
    struct sigaction act;
    act.sa_handler = DisconnectHandler;
    
    act.sa_flags = SA_RESTART;

    sigaction(SIGTERM, &act, 0);
    sigaction(SIGINT, &act, 0);
    
}
/*******************************/

static void DisconnectHandler(int signal)
{
    g_driver->Disconnect();
    
    (void)signal;
}

/*******************************/

void ConfigTasks()
{
    g_reqEngine.ConfigTask(DriverData::ActionType::READ, Read::Create);

    g_reqEngine.ConfigTask(DriverData::ActionType::WRITE, Write::Create);

    g_reqEngine.ConfigTask(DriverData::ActionType::DISCONNECT, 
                           Disconnect::Create);

    g_reqEngine.ConfigTask(DriverData::ActionType::FLUSH, Flush::Create);

    g_reqEngine.ConfigTask(DriverData::ActionType::TRIM, Trim::Create);
}