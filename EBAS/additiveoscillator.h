#ifndef ADDITIVEOSCILLATOR_H
#define ADDITIVEOSCILLATOR_H

#include <vector>

/*
 * Implements the additive Synthesys as an Oscillator.
 * Immitates the overtone spectrum of a real instrumnet
 * in order of reproducing its sound.
 */

class AdditiveOscillator
{
public:
    AdditiveOscillator();
    ~AdditiveOscillator();

    void initialize(int sampleRate);
    void setOvertones(std::vector<float> overtones);
    void setOvertoneLevels(std::vector<float> overtoneLevels);

    float getValue();
    void setGain(float gain);
    void setFrequency(float frequency);
    float getFrequency();

private:
    void calculateAbsoluteGain();

    std::vector<float> overtones;
    std::vector<float> overtoneLevels;
    std::vector<float> absoluteGain;

    float frequency;
    float gain;

    int sampleRate;
    int index;
};

#endif // ADDITIVEOSCILLATOR_H
