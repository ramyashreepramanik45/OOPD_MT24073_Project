#include "WiFi4.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
using namespace std;

WiFi4::WiFi4(FrequencyChannel &channel)
    : WiFi(20.0 * 1e6, 5.0 / 6.0, 256, 0.009, 1024, channel),
      throughput(0.0), avgLatency(0.0), maxLatency(0.0) {}

double WiFi4::generateBackoff(int collisionCount) {
    int range = min(1 << collisionCount, maxBackoffLimit);
    int slots = rand() % range;
    return slots * slotTime;
}

void WiFi4::computeMetrics() {
    avgLatency = 0.0;
    maxLatency = 0.0;

    for (const auto &user : completedUsers) {
        avgLatency += user.getLatency();
        maxLatency = max(maxLatency, user.getLatency());
    }

    avgLatency /= (completedUsers.size() > 0) ? completedUsers.size() : 1;
    throughput = (totalPackets * 1024 * 8) / (totalTime * 1e3); // Mbps
}

void WiFi4::simulate() {
    Packet packet(1024); // Packet size fixed at 1024 bytes
    double transmissionTime = calculateTransmissionTime(packet.getSize());
    bool firstTransmission = true;

    while (!activeUsers.empty()) {
        if (firstTransmission) {
            int randomIndex = rand() % activeUsers.size();
            User &selectedUser = activeUsers[randomIndex];

            if (!channel.sniff()) {
                channel.setBusy();
                selectedUser.setLatency(totalTime + transmissionTime);
                totalTime += transmissionTime;
                totalPackets++;
                channel.setIdle();

                completedUsers.push_back(selectedUser);
                activeUsers.erase(activeUsers.begin() + randomIndex);
                backoffTimes.erase(backoffTimes.begin() + randomIndex);

                for (size_t i = 0; i < activeUsers.size(); ++i) {
                    activeUsers[i].incrementCollisions();
                    backoffTimes[i] = generateBackoff(activeUsers[i].getCollisions());
                }

                firstTransmission = false;
            }
            continue;
        }

        double minBackoff = *min_element(backoffTimes.begin(), backoffTimes.end());
        vector<int> transmittingUsers;

        for (size_t i = 0; i < activeUsers.size(); ++i) {
            if (backoffTimes[i] == minBackoff) {
                transmittingUsers.push_back(i);
            }
        }

        if (transmittingUsers.size() == 1) {
            int userIdx = transmittingUsers[0];
            User &user = activeUsers[userIdx];

            if (!channel.sniff()) {
                channel.setBusy();
                user.setLatency(totalTime + minBackoff + transmissionTime);
                totalTime += minBackoff + transmissionTime;
                totalPackets++;
                channel.setIdle();

                completedUsers.push_back(user);
                activeUsers.erase(activeUsers.begin() + userIdx);
                backoffTimes.erase(backoffTimes.begin() + userIdx);
            }
        } else {
            for (int userIdx : transmittingUsers) {
                User &user = activeUsers[userIdx];
                user.incrementCollisions();
                backoffTimes[userIdx] = generateBackoff(user.getCollisions());
            }
            totalTime += minBackoff;
        }

        for (double &backoff : backoffTimes) {
            backoff -= minBackoff;
        }
    }

    computeMetrics();
}

void WiFi4::runSimulation(int numUsers) {
    activeUsers.clear();
    completedUsers.clear();
    backoffTimes.clear();
    totalTime = 0.0;
    totalPackets = 0;

    for (int i = 1; i <= numUsers; ++i) {
        activeUsers.emplace_back(i);
        backoffTimes.push_back(0.0);
    }

    simulate();
}


double WiFi4::getThroughput() const {
    return throughput;
}

double WiFi4::getAvgLatency() const {
    return avgLatency;
}

double WiFi4::getMaxLatency() const {
    return maxLatency;
}
