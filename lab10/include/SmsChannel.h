#pragma once

#include "IChannel.h"

class SmsChannel : public IChannel {
public:
    void send(const std::string& destination, const std::string& message) override;
};