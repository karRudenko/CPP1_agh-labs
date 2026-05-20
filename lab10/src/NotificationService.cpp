#include "NotificationService.h"

NotificationService::NotificationService(IChannel* channel)
    : channel_(channel) {}

void NotificationService::alert(const std::string& destination,
                                 const std::string& message) {
    channel_->send(destination, message);
}