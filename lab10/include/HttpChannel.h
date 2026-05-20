#pragma once

#include "IChannel.h"

class HttpChannel : public IChannel {
public:
    void send(const std::string& destination, const std::string& message) override;

protected:
    virtual std::string buildPayload(const std::string& destination,const std::string& message) const = 0;
    virtual std::string getUrl() const = 0;
};