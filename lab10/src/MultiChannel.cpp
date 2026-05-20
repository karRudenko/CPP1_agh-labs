#include "MultiChannel.h"

void MultiChannel::addChannel(IChannel* channel) {
    channels_.push_back(channel);
}

void MultiChannel::send(const std::string& destination, const std::string& message) {
    for (IChannel* channel : channels_) {
        channel->send(destination, message);
    }
}