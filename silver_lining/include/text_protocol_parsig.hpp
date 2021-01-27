


// about text protocol parsing class


#ifndef ILRD_HRD14_TEXT_PROTOCOL_PARSING_HPP
#define ILRD_HRD14_TEXT_PROTOCOL_PARSING_HPP

#include "parsing.hpp"

namespace hrd14
{

class TextProtocolParsing: public Parsing
{
public:
    TextProtocolParsing(size_t bufferSize);
    ~TextProtocolParsing() = default;
    TextProtocolParsing(const TextProtocolParsing&) = delete;
    TextProtocolParsing& operator=(const TextProtocolParsing&) = delete;

    std::shared_ptr<DriverData> Deserialization(const char* buffer) override;
    void Serialization(char* replyBuffer,
                       std::shared_ptr<DriverData> data) override;

    enum HeaderPart
    {
        OFFSET = 0,
        LEN,
        REQ_ID,
        REQ_TYPE
    };
private:
    size_t m_bufferSize;
};

}
#endif // ILRD_HRD14_TEXT_PROTOCOL_PARSING_HPP