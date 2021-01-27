/* Dispatcher callback solution provides an abstract API to connect
* subjects and observers under the Observer design pattern.
* Dispatcher class is coupled only with Callback-base class
* so maximum flexibility is enabled on both ends, for observer types and 
* subject types. 
* Each observer should provide a do_action function with a msg arg
* same msg arg is sent to the dispatcher from the relevant subject
* 
* Version         Date        Comments
* 0.1             20.12.20     API mentor approved
*/

#ifndef ILRD_HRD14_DISPATCHER_CALLBACK_HPP
#define ILRD_HRD14_DISPATCHER_CALLBACK_HPP

#include <list>

namespace hrd14
{
template <typename Msg>
class CallbackBase;

template <typename Msg>
class Dispatcher
{
public:
    explicit Dispatcher() = default;
    ~Dispatcher();
    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;
   
    void NotifyAll(const Msg& message);
private:
    friend class CallbackBase<Msg>;
    
    void Register(CallbackBase<Msg>* callback);
    void Unregister(CallbackBase<Msg>* callback);
    
    std::list<CallbackBase<Msg>*> m_callbacks;
};

/*******************************************/

template <typename Msg>
class CallbackBase
{
public:
    explicit CallbackBase(Dispatcher<Msg>* dispatcher);
    virtual ~CallbackBase();

    CallbackBase(const CallbackBase&) = delete;
    CallbackBase& operator=(const CallbackBase&) = delete;
     
private:
    friend class Dispatcher<Msg>;

    virtual void Notify(const Msg& message) = 0;
    virtual void EndOfService() = 0;

    Dispatcher<Msg>* m_dispacher;
};

/************************************************/

template< typename Msg, typename Observer>
class Callback : public CallbackBase<Msg>
{
public:
    using ActionFunc = void(Observer::*)(const Msg& message);
    using StopFunc = void(Observer::*)();

    explicit Callback(Dispatcher<Msg>* dispatcher, 
                      Observer& observer,
                      ActionFunc do_action,
                      StopFunc stop_action = nullptr);

    virtual ~Callback() = default; 
private:
    void Notify(const Msg& message) override;
    void EndOfService() override;

    Observer& m_observer;
    ActionFunc m_do_action;
    StopFunc m_stop_action;
};

/*******************Dispatcher*********************/

template <typename Msg>
Dispatcher<Msg>::~Dispatcher()
{
    for (auto& callback : m_callbacks)
    {
        callback->EndOfService();
        callback->m_dispacher = nullptr;
    }
}

template <typename Msg>
void Dispatcher<Msg>::NotifyAll(const Msg& message)
{
    for (auto& callback : m_callbacks)
    {
        callback->Notify(message);
    }
}

template <typename Msg>
void Dispatcher<Msg>::Register(CallbackBase<Msg>* callback)
{
    m_callbacks.emplace_back(callback);
}

template <typename Msg>
void Dispatcher<Msg>::Unregister(CallbackBase<Msg>* callback)
{
    m_callbacks.remove(callback);
}

/*******************CallbackBase*********************/
template <typename Msg>
CallbackBase<Msg>::CallbackBase(Dispatcher<Msg>* dispatcher) : m_dispacher(dispatcher)
{
    m_dispacher->Register(this);
}

template <typename Msg>
CallbackBase<Msg>::~CallbackBase()
{
    if(m_dispacher)
    {
        m_dispacher->Unregister(this);
    }
}   

/*******************Callback*********************/

template<typename Msg, typename Observer>
Callback<Msg, Observer>::Callback(Dispatcher<Msg>* dispatcher, 
                                  Observer& observer,
                                  ActionFunc do_action,
                                  StopFunc stop_action) : CallbackBase<Msg>(dispatcher),
                                                          m_observer(observer),
                                                          m_do_action(do_action),
                                                          m_stop_action(stop_action)
{}


template <typename Msg, typename Observer>
void Callback<Msg, Observer>::Notify(const Msg& message)
{
    (m_observer.*m_do_action)(message);
}


template <typename Msg, typename Observer>
void Callback<Msg, Observer>::EndOfService()
{
    if(m_stop_action)
    {
        (m_observer.*m_stop_action)();
    }
}

}//namespace hrd14

#endif //ILRD_HRD14_DISPATCHER_CALLBACK_HPP
