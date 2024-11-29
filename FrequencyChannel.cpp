#include "FrequencyChannel.h"

FrequencyChannel::FrequencyChannel() : isBusy(false) {}

bool FrequencyChannel::sniff() const {
    return isBusy;
}

void FrequencyChannel::setBusy() {
    isBusy = true;
}

void FrequencyChannel::setIdle() {
    isBusy = false;
}
