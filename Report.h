#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

struct Metrics {
    std::string simulationType;
    int numUsers;
    double throughput;   
    double avgLatency;   
    double maxLatency;   
};

class Report {
private:
    std::vector<Metrics> metricsLog;

public:
    void addMetrics(const std::string &type, int users, double throughput, double avgLatency, double maxLatency);
    void printReport() const;
    void clearReport();
};

#endif // REPORT_H
