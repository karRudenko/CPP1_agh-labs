#pragma once

#include "HttpChannel.h"

class SlackChannel : public HttpChannel {
protected:
    std::string buildPayload(const std::string& destination, const std::string& message) const override;
    std::string getUrl() const override;
};