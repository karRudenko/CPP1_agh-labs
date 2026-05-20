#include "TeamsChannel.h"

std::string TeamsChannel::buildPayload(const std::string& destination,
                                       const std::string& message) const {
    return "group=" + destination + "&text=" + message;
}

std::string TeamsChannel::getUrl() const {
    return "https://teams.example/send";
}