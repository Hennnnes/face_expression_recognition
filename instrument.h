#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <vector>
#include "additiveoscillator.h"
#include "envelope.h"

/*
 * Combines multiple Oscillators and Envelopes to form a
 * polyphonic Instrument.
 * Sends the Note-On/-Off Events to a available Oscillator.
 */

class Instrument
{
public:
    Instrument();
    ~Instrument();
    void initialize(int sampleRate, int num_osc);
    void setInstrument(int type);
    void set_num_osc(int num);
    int get_num_osc();
    bool isAvailable();

    float getValue();
    void on(float frequency, float velocity);
    void off(float frequency);

    enum Type{PIANO,OFF};

private:
    int indexOfAvailableOsc();

    std::vector<AdditiveOscillator*> osc;
    std::vector<Envelope*> env;

    int sampleRate;
    Type type;
    int num_osc;
    bool available;
};

#endif // INSTRUMENT_H
