#pragma once

#include <string>

class IChannel {
public:
    virtual void send(const std::string& destination, const std::string& message) = 0;
    virtual ~IChannel() = default;
};