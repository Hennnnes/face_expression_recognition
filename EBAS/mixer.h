#ifndef MIXER_H
#define MIXER_H

#include <vector>
#include "instrument.h"

class Mixer
{
public:
    Mixer();
    ~Mixer();
    void initialize(int sampleRate,int num_instruments);
    void on(float frequency, float velocity);
    void off(float frequency);
    float getValue();

private:
    std::vector<Instrument*> instruments;
    int sampleRate;

};

#endif // MIXER_H
