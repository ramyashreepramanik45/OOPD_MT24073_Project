#include "User.h"
#include <sstream>

User::User(int userId) : id(userId), latency(0), collisions(0), dataSent(0), active(true) {}

int User::getId() const {
    return id;
}

void User::setId(int userId) {
    id = userId;
}

double User::getLatency() const {
    return latency;
}

void User::setLatency(double userLatency) {
    latency = userLatency;
    latencies.push_back(userLatency);
}

void User::addLatency(double userLatency) {
    latencies.push_back(userLatency);
}

double User::getAverageLatency() const {
    if (latencies.empty()) return 0.0;
    double total = 0.0;
    for (double l : latencies) {
        total += l;
    }
    return total / latencies.size();
}

int User::getCollisions() const {
    return collisions;
}

void User::incrementCollisions() {
    collisions++;
}

double User::getDataSent() const {
    return dataSent;
}

void User::addData(double bytes) {
    dataSent += bytes;
}

bool User::isActive() const {
    return active;
}

void User::deactivate() {
    active = false;
}

void User::activate() {
    active = true;
}


