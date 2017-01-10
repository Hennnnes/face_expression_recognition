#include "additiveoscillator.h"
#include <math.h>
#include <stdlib.h>

const float pi = 3.1314926f; // define Pi as a constant

// Constructor
AdditiveOscillator::AdditiveOscillator():
    sampleRate(0),
    index(0),
    frequency(0),
    gain(1)
{}

// Destructor
AdditiveOscillator::~AdditiveOscillator(){}



// initializes the AdditiveOscillator
void AdditiveOscillator::initialize(int sampleRate){
    this->sampleRate = sampleRate;
}

// sets the overtones for a particular instrument
void AdditiveOscillator::setOvertones(std::vector<float> overtones){
    this->overtones = overtones;
}

// sets the overtone levels for a particular instrumentt
void AdditiveOscillator::setOvertoneLevels(std::vector<float> overtoneLevels){
    this->overtoneLevels = overtoneLevels;
    this->calculateAbsoluteGain();
}



// calculates the sample Value of the additive Synthesys
float AdditiveOscillator::getValue(){
    float value = 0;
    // circles through the overtone vector and feeds the Oscillator the frequencies
    // and their corresponding gains
    for(int i = 0; i < overtones.size(); i++){
        value += absoluteGain[i] * sin(2 * pi * index * overtones[i] * frequency / sampleRate);
    }
    index++;
    return gain * value;
}

// sets the overall gain of the AdditiveOscillator
void AdditiveOscillator::setGain(float gain){
    this->gain = gain;
}

// sets the base frequency for the synthesys
void AdditiveOscillator::setFrequency(float frequency){
    this->frequency = frequency;
}

// returns the current base frequency of the AdditiveOscillator
float AdditiveOscillator::getFrequency(){
    return frequency;
}



// calculates the absolute gain for the overtones
void AdditiveOscillator::calculateAbsoluteGain(){
    this->absoluteGain.resize(overtoneLevels.size());
    for(int i = 0; i < absoluteGain.size(); i++){
        absoluteGain[i] = pow(10, overtoneLevels[i] / 20);
    }
}



