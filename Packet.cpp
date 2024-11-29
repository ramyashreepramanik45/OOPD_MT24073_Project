#include "Packet.h"

Packet::Packet(int packetSize) : size(packetSize) {}

int Packet::getSize() const {
    return size;
}
