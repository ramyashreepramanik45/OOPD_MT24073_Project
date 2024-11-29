#include "WiFi.h"
#include <cmath> 


WiFi::WiFi(double bw, double cr, int mo, double st, int mbl, FrequencyChannel &ch)
    : bandwidth(bw), codingRate(cr), modulationOrder(mo), slotTime(st), maxBackoffLimit(mbl), channel(ch) {}

double WiFi::calculateTransmissionRate() const {
    return bandwidth * codingRate * log2(modulationOrder);
}

double WiFi::calculateTransmissionTime(int packetSize) const {
    double transmissionRate = calculateTransmissionRate();
    return (packetSize * 8) / transmissionRate * 1e3; 
}
