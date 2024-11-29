#ifndef PACKET_H
#define PACKET_H

class Packet {
private:
    int size; 

public:
    Packet(int packetSize = 1024); 
    int getSize() const;
};

#endif
