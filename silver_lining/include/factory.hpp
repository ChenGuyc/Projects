/*
* Factory is based on Factory design pattern 
* User must supply public static create method/functor for each derived class
*
* Base- Base class name
* Key- unique key for each derived class
* Args-  arguments struct for derived class create method
*
Version         Date        Comments
0.1             10.12.20     API mentor approved
*/

#ifndef ILRD_HRD14_FACTORY_HPP
#define ILRD_HRD14_FACTORY_HPP

#include <functional>
#include <unordered_map>
#include <functional>
#include <memory>

namespace hrd14
{

template <typename Base, typename Key, typename Args>
class Factory
{

public:

    enum add_status
    {
        ADD = 0,
        REPLACE
    };

    Factory() = default;
    Factory(const Factory&)= delete;
    Factory& operator=(const Factory&) = delete;
    ~Factory() = default;
     
    //may throw bad_alloc exception
    using CreatorFunc = std::function<std::shared_ptr<Base>(Args args)>;
    
    //may throw bad_alloc exception
    //if key allready exist Add will replace the createFunc
    add_status Add(const Key& key, CreatorFunc createFunc);
    
    //may throw bad_alloc exception or logical_error
    std::shared_ptr<Base> Create(const Key& key, Args args);

private:

    std::unordered_map<Key, CreatorFunc> m_creators;
};


template <typename Base, typename Key, typename Args>
typename Factory<Base, Key, Args>::add_status Factory<Base, Key, Args>::Add(
                                    const Key& key, CreatorFunc createFunc)
{
    if (m_creators.end() != m_creators.find(key)) // key exist
    {
        m_creators[key] = createFunc;
        return (REPLACE);
    }

    m_creators.insert(std::make_pair(key, createFunc));
    return (ADD);
}

template <typename Base, typename Key, typename Args>
std::shared_ptr<Base> Factory<Base, Key, Args>::Create(
                             const Key& key, Args args)
{
    return (m_creators.at(key)(args));
}

}//namespace hrd14

#endif //ILRD_HRD14_FACTORY_HPP
