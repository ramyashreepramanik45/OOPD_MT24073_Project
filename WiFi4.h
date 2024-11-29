#ifndef WIFI4_H
#define WIFI4_H

#include "WiFi.h"
#include "User.h"
#include "Packet.h"
#include <vector>

class WiFi4 : public WiFi {
private:
    double throughput;  
    double avgLatency;  
    double maxLatency;  

    std::vector<User> activeUsers;
    std::vector<User> completedUsers;
    std::vector<double> backoffTimes;
    double totalTime = 0.0;
    int totalPackets = 0;

    double generateBackoff(int collisionCount);
    void computeMetrics(); 
    void simulate();       

public:
    WiFi4(FrequencyChannel &channel);
    void runSimulation(int numUsers) override;

    // Getters for metrics
    double getThroughput() const;
    double getAvgLatency() const;
    double getMaxLatency() const;
};

#endif
