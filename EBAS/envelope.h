#ifndef ENVELOPE_H
#define ENVELOPE_H

/*
 * Implements the ADSR-Envelope which processes the samples
 * generatet by the Oscillators.
 * There is the option between a continously decaying envelope
 * and a constant level sustain one.
 * The decaying varialble determines which of the two options
 * is applied to the input samples.
 */

class Envelope
{
public:
    Envelope();
    ~Envelope();

    void initialize(int sampleRate);
    void setAttackSeconds(float seconds);
    void setDecaySeconds(float seconds);
    void setReleaseSeconds(float seconds);
    void setSustainLevel(float dB);
    void setDecayLoss(float dB_per_second);
    void setDecaying(bool decaying);

    float process(float input);
    void on();
    void off();
    bool isAvailable();

    enum State{OFF, ATTACK, DECAY, SUSTAIN, RELEASE};

private:
    void setState(State state);

    float attackSeconds;
    float decaySeconds;
    float releaseSeconds;
    float sustain_dB;
    float sustain_gain;
    float decay_dB_per_sec;
    bool decaying;
    float gain;
    float gainChange;

    State state;
    int sampleRate;
};

#endif // ENVELOPE_H
