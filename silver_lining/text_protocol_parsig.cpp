/*********************************************
 * file name: text_protocol_parsing.cpp      *
 * developer: Guy Chen                       *
 * date: 03.01.21                            *
 * version 0.1                               *
 *********************************************/

#include <cstring>  // memcpy

#include "text_protocol_parsig.hpp"

namespace hrd14
{
TextProtocolParsing::TextProtocolParsing(size_t bufferSize) 
                    : m_bufferSize(bufferSize)
{}

std::shared_ptr<DriverData> TextProtocolParsing::Deserialization(const char request[])
{
    std::string header = request;
    std::string headerParts[4];
    size_t oldPos = 0;
    size_t newPos = 0;
    
    for (size_t i = 0; i < 4; ++i)
    {
        newPos = header.find(';', oldPos);
        headerParts[i] = header.substr(oldPos, newPos - oldPos);
        oldPos = newPos + 1;
    }

    size_t beginData = ++oldPos;
    auto data = std::make_shared<DriverData>(std::stoull(headerParts[LEN]));

    data->m_internalID = std::stoi(headerParts[REQ_ID]);

    data->m_from = std::stoull(headerParts[OFFSET]);

    data->m_type = static_cast<DriverData::ActionType>
                                (std::stoi(headerParts[REQ_TYPE]));

    if (data->m_type == DriverData::ActionType::WRITE)
    {
        memcpy(data->m_buffer.data(), &request[beginData], data->m_len);
    }

    return (data);
}

void TextProtocolParsing::Serialization(char* replyBuffer,
                               std::shared_ptr<DriverData> data)
{
    std::string header = std::to_string(data->m_len);
    header += ";";
    header += std::to_string(data->m_internalID);
    header += ";";
    header += std::to_string(data->m_type);
    
    size_t headerLen = header.length();
    memcpy(replyBuffer, header.c_str(), headerLen);

    replyBuffer[headerLen] = '\0';

    if (data->m_type == DriverData::ActionType::READ)
    {
        memcpy(&replyBuffer[headerLen + 1], data->m_buffer.data(), data->m_len);
        for (size_t i = headerLen + 1 + data->m_len; 
             i < m_bufferSize;
             ++i)
        {
            replyBuffer[i] = 0;
        }
    }
    else
    {
        for (size_t i = headerLen + 1; 
             i < m_bufferSize;
             ++i)
        {
            replyBuffer[i] = 0;
        }
    }
}

} // namespace hrd14
