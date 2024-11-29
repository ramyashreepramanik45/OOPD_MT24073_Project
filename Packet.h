#ifndef PACKET_H
#define PACKET_H

class Packet {
private:
    int size; // Packet size in bytes

public:
    Packet(int packetSize = 1024); // Constructor with default size
    int getSize() const;
};

#endif
