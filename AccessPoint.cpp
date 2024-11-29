#include "AccessPoint.h"
#include <algorithm>
#include <iostream>

AccessPoint::AccessPoint(FrequencyChannel &freqChannel)
    : channel(freqChannel), activeConnections(0), totalDataTransmitted(0.0), signalStrength(-50.0) {}

bool AccessPoint::canTransmit() const {
    return !channel.sniff();
}

void AccessPoint::startTransmission() {
    channel.setBusy();
    logActivity("Transmission started.");
}

void AccessPoint::endTransmission() {
    channel.setIdle();
    logActivity("Transmission ended.");
}

void AccessPoint::addConnection() {
    activeConnections++;
}

void AccessPoint::removeConnection() {
    if (activeConnections > 0) {
        activeConnections--;
    }
}

int AccessPoint::getActiveConnections() const {
    return activeConnections;
}

void AccessPoint::recordDataTransmission(double dataSize) {
    totalDataTransmitted += dataSize;
    logActivity("Recorded data transmission: " + std::to_string(dataSize) + " bytes.");
}

double AccessPoint::getTotalDataTransmitted() const {
    return totalDataTransmitted;
}

void AccessPoint::setSignalStrength(double strength) {
    signalStrength = strength;
    logActivity("Signal strength updated to " + std::to_string(strength) + " dBm.");
}

double AccessPoint::getSignalStrength() const {
    return signalStrength;
}

void AccessPoint::connectDevice(int deviceId) {
    connectedDevices.push_back(deviceId);
    logActivity("Device " + std::to_string(deviceId) + " connected.");
}

void AccessPoint::disconnectDevice(int deviceId) {
    connectedDevices.erase(std::remove(connectedDevices.begin(), connectedDevices.end(), deviceId), connectedDevices.end());
    logActivity("Device " + std::to_string(deviceId) + " disconnected.");
}

const std::vector<int>& AccessPoint::getConnectedDevices() const {
    return connectedDevices;
}

void AccessPoint::logActivity(const std::string &activity) {
    logs.push_back(activity);
}

void AccessPoint::printLogs() const {
    for (const auto &log : logs) {
        std::cout << log << std::endl;
    }
}

void AccessPoint::clearLogs() {
    logs.clear();
    logActivity("Logs cleared.");
}
