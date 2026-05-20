#include "SmsChannel.h"
#include <iostream>

void SmsChannel::send(const std::string& destination, const std::string& message) {
    std::cout << "SMS to " << destination << ": " << message << "\n";
}