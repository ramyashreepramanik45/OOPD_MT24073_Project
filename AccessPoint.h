#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include "FrequencyChannel.h"
#include <string>
#include <vector>

class AccessPoint {
private:
    FrequencyChannel &channel;
    int activeConnections;
    double totalDataTransmitted;
    double signalStrength;
    std::vector<int> connectedDevices;
    std::vector<std::string> logs;

public:
    AccessPoint(FrequencyChannel &freqChannel);

    bool canTransmit() const;
    void startTransmission();
    void endTransmission();

    void addConnection();
    void removeConnection();
    int getActiveConnections() const;

    void recordDataTransmission(double dataSize);
    double getTotalDataTransmitted() const;

    void setSignalStrength(double strength);
    double getSignalStrength() const;

    void connectDevice(int deviceId);
    void disconnectDevice(int deviceId);
    const std::vector<int>& getConnectedDevices() const;

    void logActivity(const std::string &activity);
    void printLogs() const;
    void clearLogs();
};

#endif
