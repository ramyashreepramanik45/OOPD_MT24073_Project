#ifndef WIFI5_H
#define WIFI5_H

#include "WiFi.h"
#include <iostream>
#include <cmath>

class WiFi5 : public WiFi {
private:
    const double parallelCommunicationTime; 
    double transmissionRate;               
    double broadcastTime;                  
    double csiTimePerUser;                 
    double totalTime;                      
    double totalLatency; 
    double avgLatency;                  
    double maxLatency;                     
    double throughput;                     

    void initializeMetrics(); 

public:
    WiFi5(FrequencyChannel &channel);

    void runSimulation(int numUsers) override;

  
    double getThroughput() const;
    double getAvgLatency() const;
    double getMaxLatency() const;
};

#endif // WIFI5_H
