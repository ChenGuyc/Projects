


// about parsing class


#ifndef ILRD_HRD14_PARSING_HPP
#define ILRD_HRD14_PARSING_HPP

#include <memory>   // std::shared_ptr

#include "driver_data.hpp"

namespace hrd14
{

class Parsing
{
public:
    Parsing() = default;
    ~Parsing() = default;
    Parsing(const Parsing&) = delete;
    Parsing& operator=(const Parsing&) = delete;

    virtual std::shared_ptr<DriverData> Deserialization(const char* buffer) = 0;
    virtual void Serialization(char* dest,
                               std::shared_ptr<DriverData> data) = 0;
private:

};

}
#endif // ILRD_HRD14_PARSING_HPP