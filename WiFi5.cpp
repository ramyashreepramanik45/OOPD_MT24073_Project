#include "WiFi5.h"
#include <iostream>
#include <cmath>
using namespace std;

WiFi5::WiFi5(FrequencyChannel &channel)
    : WiFi(20.0 * 1e6, 5.0 / 6.0, 256, 0.009, 1024, channel),
      parallelCommunicationTime(15.0),
      transmissionRate(0.0),
      broadcastTime(0.0),
      csiTimePerUser(0.0),
      totalTime(0.0),
      totalLatency(0.0),
      avgLatency(0.0),
      maxLatency(0.0),
      throughput(0.0) {}

void WiFi5::initializeMetrics() {
    transmissionRate = calculateTransmissionRate();
    broadcastTime = (1024 * 8) / transmissionRate * 1000; // Broadcast time for 1 packet (ms)
    csiTimePerUser = (200 * 8) / transmissionRate * 1000; // CSI time per user (ms)
    totalTime = 0.0;
    totalLatency = 0.0;
    avgLatency = 0.0;
    maxLatency = 0.0;
    throughput = 0.0;
}

void WiFi5::runSimulation(int numUsers) {
    int numRounds;
    cout << "Enter the number of rounds: ";
    cin >> numRounds;

    initializeMetrics();

    double transmissionTime = (1024 * 8) / transmissionRate * 1000; // Transmission time per packet (ms)
    int packetsPerUserIn15ms = static_cast<int>(floor(parallelCommunicationTime / transmissionTime));

    for (int round = 1; round <= numRounds; ++round) {
        double roundTime = broadcastTime;

        for (int user = 1; user <= numUsers; ++user) {
            double userLatency = roundTime + user * csiTimePerUser;
            totalLatency += userLatency;
            maxLatency = max(maxLatency, userLatency);
        }

        // Add parallel communication time
        roundTime += numUsers * csiTimePerUser + parallelCommunicationTime;
        totalTime += roundTime;
    }

    // Calculate throughput: Total data transmitted in all rounds divided by total time
    throughput = ((numUsers * numRounds * packetsPerUserIn15ms * 1024 * 8) / (totalTime / 1000)) / 1e6; // in Mbps
    avgLatency = totalLatency / (numUsers * numRounds);

    this->avgLatency = avgLatency;
    this->maxLatency = maxLatency;
    this->throughput = throughput;

    cout << "\nWiFi5 Simulation Info:\n";
    cout << "Number of Users: " << numUsers << "\n";
    cout << "Number of Rounds: " << numRounds << "\n";
    cout << "Transmission Time per Packet: " << transmissionTime << " ms\n";
    cout << "Packets Per User in 15 ms: " << packetsPerUserIn15ms << "\n";
    cout << "Total Time: " << totalTime << " ms\n";
    cout << "Average Latency: " << avgLatency << " ms\n";
    cout << "Max Latency: " << maxLatency << " ms\n";
    cout << "Throughput: " << throughput << " Mbps\n";
}

double WiFi5::getThroughput() const {
    return throughput;
}

double WiFi5::getAvgLatency() const {
    return avgLatency;
}

double WiFi5::getMaxLatency() const {
    return maxLatency;
}

