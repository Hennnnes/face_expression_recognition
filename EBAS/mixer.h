#ifndef MIXER_H
#define MIXER_H

#include <vector>
#include "instrument.h"

class Mixer
{
public:
    Mixer();
    ~Mixer();

    void initialize(int sampleRate);
    float getValue();

    void on(float frequency, float velocity, int channel);
    void off(float frequency, float channel);

private:
    std::vector<Instrument*> instruments;
    int num_instruments;
    int sampleRate;
};

#endif // MIXER_H
