#pragma once

#include "IChannel.h"

class NotificationService {
public:
    explicit NotificationService(IChannel* channel);
    void alert(const std::string& destination, const std::string& message);

private:
    IChannel* channel_;
};