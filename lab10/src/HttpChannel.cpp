#include "HttpChannel.h"
#include <iostream>

void HttpChannel::send(const std::string& destination, const std::string& message) {
    const std::string payload = buildPayload(destination, message);
    std::cout << "HTTP request to " << getUrl() << ": " << payload << "\n";
}