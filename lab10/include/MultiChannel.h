#pragma once

#include "IChannel.h"
#include <vector>

class MultiChannel : public IChannel {
public:
    void addChannel(IChannel* channel);
    void send(const std::string& destination, const std::string& message) override;

private:
    std::vector<IChannel*> channels_;
};