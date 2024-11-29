#include "Report.h"
using namespace std;

void Report::addMetrics(const string &type, int users, double throughput, double avgLatency, double maxLatency) {
    metricsLog.push_back({type, users, throughput, avgLatency, maxLatency});
}

void Report::printReport() const {
    cout << "\n--- Simulation Metrics Report ---\n";
    cout << setw(15) << "Type" 
              << setw(10) << "Users" 
              << setw(15) << "Throughput (Mbps)" 
              << setw(20) << "Avg Latency (ms)" 
              << setw(20) << "Max Latency (ms)" << "\n";

    for (const auto &metric : metricsLog) {
        cout << setw(15) << metric.simulationType
                  << setw(10) << metric.numUsers
                  << setw(15) << fixed << setprecision(2) << metric.throughput
                  << setw(20) << metric.avgLatency
                  << setw(20) << metric.maxLatency << "\n";
    }
}

void Report::clearReport() {
    metricsLog.clear();
    cout << "Report cleared.\n";
}
