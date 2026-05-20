#include "SlackChannel.h"

std::string SlackChannel::buildPayload(const std::string& destination,
                                       const std::string& message) const {
    return "channel=" + destination + "&message=" + message;
}

std::string SlackChannel::getUrl() const {
    return "https://slack.example/send";
}