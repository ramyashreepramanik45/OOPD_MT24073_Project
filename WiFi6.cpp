#include "WiFi6.h"
#include <iostream>
#include <queue>
using namespace std;

WiFi6::WiFi6(FrequencyChannel &channel)
    : WiFi(20.0 * 1e6, 5.0 / 6.0, 256, 0.009, 1024, channel),
      subdivisionBandwidth(2),
      communicationTime(5.0),
      transmissionRate(0.0),
      totalLatency(0.0),
      maxLatency(0.0),
      totalTime(0.0) {}

void WiFi6::initializeMetrics() {
    transmissionRate = subdivisionBandwidth * 1e6 * 5.0 / 6.0 * log2(256);
    totalLatency = 0.0;
    maxLatency = 0.0;
    totalTime = 0.0;
    throughput = 0.0;
}

void WiFi6::computeMetrics(queue<int>& userQueue, int numChannels) {
    initializeMetrics();

    int numUsers = userQueue.size();
    int rounds = 0;

    while (!userQueue.empty()) {
        int roundUsers = min(numChannels, static_cast<int>(userQueue.size()));
        rounds++;

        for (int i = 0; i < roundUsers; ++i) {
            int userIndex = userQueue.front();
            userQueue.pop();

            double packetSize = 1024 * 8; 
            transmissionTime = packetSize / transmissionRate * 1e3; // Update member variable
            double userLatency = (rounds - 1) * communicationTime + transmissionTime;

            totalLatency += userLatency;
            maxLatency = max(maxLatency, userLatency);
        }

        totalTime = rounds * communicationTime;
    }
}

void WiFi6::printResults(int numUsers, int numChannels) {
    int totalpacket = (floor(totalTime / transmissionTime));
    throughput = (numUsers * totalpacket * 1024 * 8) / (totalTime * 1e3); 
    double avgLatency = totalLatency / numUsers;

    cout << "\nWiFi6 Simulation Info:\n";
    cout << "Number of Users: " << numUsers << "\n";
    cout << "Subdivision Bandwidth: " << subdivisionBandwidth << " MHz\n";
    cout << "Transmission rate: " << transmissionRate/1e6 << "Mbps\n";
    cout << "Number of Channels: " << numChannels << "\n";
    
}

void WiFi6::runSimulation(int numUsers) {
    if (numUsers <= 0) {
        cout << "Invalid number of users! Exiting simulation.\n";
        return;
    }

    cout << "Enter the subdivision bandwidth (2, 4, 10 MHz): ";
    cin >> subdivisionBandwidth;

    if (subdivisionBandwidth != 2 && subdivisionBandwidth != 4 && subdivisionBandwidth != 10) {
        cout << "Invalid subdivision bandwidth! Defaulting to 2 MHz.\n";
        subdivisionBandwidth = 2;
    }

    int numChannels = 20 / subdivisionBandwidth;

    queue<int> userQueue;
    for (int i = 0; i < numUsers; ++i) {
        userQueue.push(i); 
    }

    computeMetrics(userQueue, numChannels);
    printResults(numUsers, numChannels);
}


double WiFi6::getThroughput(int numUsers) const {
    return throughput; 
}

double WiFi6::getAvgLatency(int numUsers) const {
    return totalLatency / numUsers; 
}

double WiFi6::getMaxLatency() const {
    return maxLatency; 
}
