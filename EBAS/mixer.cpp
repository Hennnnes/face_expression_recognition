#include "mixer.h"


// Constructor
Mixer::Mixer()
{

}

// Destructor
Mixer::~Mixer(){
    if(instruments.size() != 0){
        for(int i = 0; i < instruments.size(); i++){
            delete instruments[i];
        }
    }
}

// Initializes all the needed Instruments
void Mixer::initialize(int sampleRate, int num_instruments){
    this->sampleRate = sampleRate;
    // Deletes the old Instruments
    if(instruments.size() != 0){
        for(int i = 0; i < instruments.size(); i++){
            delete instruments[i];
        }
    }
    // creates the new Instruments
    instruments.resize(num_instruments);
    for(int i = 0; i < instruments.size(); i++){
        instruments[i] = new Instrument();
        instruments[i]->initialize(this->sampleRate, 4);
    }
}

// Return the Samples of the sum signal
float Mixer::getValue(){
    float value = 0;
    // calculates the sum of all Instruments
    for(int i = 0; i < instruments.size(); i++){
        value += instruments[i] -> getValue();
    }
    return value;
}

// Note on
void Mixer::on(float frequency, float velocity){
    instruments[0]->on(frequency,velocity);
}

// Note off
void Mixer::off(float frequency)
{
    instruments[0]->off(frequency);
}
