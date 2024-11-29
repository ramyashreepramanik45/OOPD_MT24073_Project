#ifndef WIFI_H
#define WIFI_H

#include "FrequencyChannel.h"
#include "User.h"
#include "Packet.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>

class WiFi {
protected:
    double bandwidth;
    double codingRate;
    int modulationOrder;
    double slotTime;
    int maxBackoffLimit;
    FrequencyChannel &channel;

    double calculateTransmissionRate() const;
    double calculateTransmissionTime(int packetSize) const;

public:
    WiFi(double bw, double cr, int mo, double st, int mbl, FrequencyChannel &ch);
    virtual ~WiFi() = default;
    virtual void runSimulation(int numUsers) = 0;
};

#endif
