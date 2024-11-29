#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
private:
    int id;
    double latency;
    int collisions;
    double dataSent;
    bool active;
    std::vector<double> latencies;

public:
    User(int userId);
    int getId() const;
    void setId(int userId);
    double getLatency() const;
    void setLatency(double userLatency);
    void addLatency(double userLatency);
    double getAverageLatency() const;
    int getCollisions() const;
    void incrementCollisions();
    double getDataSent() const;
    void addData(double bytes);
    bool isActive() const;
    void deactivate();
    void activate();
    
};

#endif
