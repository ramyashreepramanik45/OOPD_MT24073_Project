#include "WiFi4.h"
#include "WiFi5.h"
#include "WiFi6.h"
#include "FrequencyChannel.h"
#include "AccessPoint.h"
#include "Report.h"
#include <iostream>
#include <iomanip>
#include <stdexcept> // For exception handling
using namespace std;

int main() {
    FrequencyChannel channel;
    AccessPoint accessPoint(channel);
    Report report;
    bool exitProgram = false;
    bool useLogs = false;

    while (!exitProgram) {
        try {
            int choice;
            cout << "\n--- Menu ---\n";
            cout << "1. Run WiFi4 Simulation\n";
            cout << "2. Run WiFi5 Simulation\n";
            cout << "3. Run WiFi6 Simulation\n";
            cout << "4. View Logs\n";
            cout << "5. Clear Logs\n";
            cout << "6. View Metrics Report\n";
            cout << "7. Clear Metrics Report\n";
            cout << "8. Toggle Logging (" << (useLogs ? "Enabled" : "Disabled") << ")\n";
            cout << "9. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 9) {
                cin.clear();                // Clear the input stream
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                throw invalid_argument("Invalid menu choice. Please enter a number between 1 and 9.");
            }

            switch (choice) {
                case 1: {
                    try {
                        int numUsers;
                        cout << "Enter the number of users for WiFi4: ";
                        cin >> numUsers;
                        if (cin.fail() || numUsers <= 0) {
                            throw invalid_argument("Number of users must be a positive integer.");
                        }

                        if (useLogs) accessPoint.logActivity("Running WiFi4 Simulation.");
                        WiFi4 wifi4(channel);
                        wifi4.runSimulation(numUsers);

                        cout << "\nWiFi4 Simulation Results:\n";
                        cout << fixed << setprecision(5);
                        cout << "Throughput: " << wifi4.getThroughput() << " Mbps\n";
                        cout << "Average Latency: " << wifi4.getAvgLatency() << " ms\n";
                        cout << "Maximum Latency: " << wifi4.getMaxLatency() << " ms\n";

                        report.addMetrics("WiFi4", numUsers, wifi4.getThroughput(), wifi4.getAvgLatency(), wifi4.getMaxLatency());
                    } catch (const exception &e) {
                        cerr << "Error in WiFi4 simulation: " << e.what() << endl;
                    }
                    break;
                }
                case 2: {
                    try {
                        int numUsers;
                        cout << "Enter the number of users for WiFi5: ";
                        cin >> numUsers;
                        if (cin.fail() || numUsers <= 0) {
                            throw invalid_argument("Number of users must be a positive integer.");
                        }

                        if (useLogs) accessPoint.logActivity("Running WiFi5 Simulation.");
                        WiFi5 wifi5(channel);
                        wifi5.runSimulation(numUsers);

                        cout << "\nWiFi5 Simulation Results:\n";
                        cout << fixed << setprecision(5);
                        cout << "Throughput: " << wifi5.getThroughput() << " Mbps\n";
                        cout << "Average Latency: " << wifi5.getAvgLatency() << " ms\n";
                        cout << "Maximum Latency: " << wifi5.getMaxLatency() << " ms\n";

                        report.addMetrics("WiFi5", numUsers, wifi5.getThroughput(), wifi5.getAvgLatency(), wifi5.getMaxLatency());
                    } catch (const exception &e) {
                        cerr << "Error in WiFi5 simulation: " << e.what() << endl;
                    }
                    break;
                }
                case 3: {
                    try {
                        int numUsers;
                        cout << "Enter the number of users for WiFi6: ";
                        cin >> numUsers;
                        if (cin.fail() || numUsers <= 0) {
                            throw invalid_argument("Number of users must be a positive integer.");
                        }

                        if (useLogs) accessPoint.logActivity("Running WiFi6 Simulation.");
                        WiFi6 wifi6(channel);
                        wifi6.runSimulation(numUsers);

                        cout << "\nWiFi6 Simulation Results:\n";
                        cout << fixed << setprecision(5);
                        cout << "Throughput: " << wifi6.getThroughput(numUsers) << " Mbps\n";
                        cout << "Average Latency: " << wifi6.getAvgLatency(numUsers) << " ms\n";
                        cout << "Maximum Latency: " << wifi6.getMaxLatency() << " ms\n";

                        report.addMetrics("WiFi6", numUsers, wifi6.getThroughput(numUsers), wifi6.getAvgLatency(numUsers), wifi6.getMaxLatency());
                    } catch (const exception &e) {
                        cerr << "Error in WiFi6 simulation: " << e.what() << endl;
                    }
                    break;
                }
                case 4: {
                    cout << "\nSimulation Logs:\n";
                    accessPoint.printLogs();
                    break;
                }
                case 5: {
                    accessPoint.clearLogs();
                    cout << "Logs cleared.\n";
                    break;
                }
                case 6: {
                    report.printReport();
                    break;
                }
                case 7: {
                    report.clearReport();
                    cout << "Metrics report cleared.\n";
                    break;
                }
                case 8: {
                    useLogs = !useLogs;
                    cout << "Logging is now " << (useLogs ? "enabled." : "disabled.") << endl;
                    break;
                }
                case 9:
                    exitProgram = true;
                    cout << "Exiting program.\n";
                    break;
                default:
                    throw runtime_error("Unexpected error in menu choice handling.");
            }
        } catch (const exception &e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    return 0;
}
