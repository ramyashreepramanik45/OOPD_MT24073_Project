#ifndef WIFI6_H
#define WIFI6_H

#include "WiFi.h"
#include <queue>
#include <iostream>

class WiFi6 : public WiFi {
private:
    int subdivisionBandwidth;
    const double communicationTime;
    double transmissionRate;
    double totalLatency;
    double maxLatency;
    double totalTime;
    double throughput;   
    double avgLatency;
    double transmissionTime; 

    void initializeMetrics();
    void computeMetrics(std::queue<int>& userQueue, int numChannels);
    void printResults(int numUsers, int numChannels);

public:
    WiFi6(FrequencyChannel &channel);
    void runSimulation(int numUsers) override;

    
    double getThroughput(int numUsers) const;
    double getAvgLatency(int numUsers) const;
    double getMaxLatency() const;
};

#endif // WIFI6_H
