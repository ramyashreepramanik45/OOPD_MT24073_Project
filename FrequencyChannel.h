#ifndef FREQUENCYCHANNEL_H
#define FREQUENCYCHANNEL_H

class FrequencyChannel {
private:
    bool isBusy;

public:
    FrequencyChannel();
    bool sniff() const;
    void setBusy();
    void setIdle();
};

#endif
