#include "mixer.h"
#include <QDebug>

Mixer::Mixer():
    num_instruments(2),
    sampleRate(44100)
{

}

Mixer::~Mixer(){
    if(instruments.size() != 0){
        for(int i = 0; i < instruments.size(); i++){
            delete instruments[i];
        }
    }
    qDebug() << "~Mixer";
}

// Initializes all the needed Instruments
void Mixer::initialize(int sampleRate){
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
        instruments[i]->initialize(this->sampleRate, 10);
        qDebug() << "Mixer: Instrument" << i << "initialized";
    }

    qDebug() << "Mixer initialized";
}

// Return the Samples of the sum signal
float Mixer::getValue(){
    float value = 0;

    // calculates the sum of all Instruments
    for(int i = 0; i < instruments.size(); i++){
       value += instruments[i] -> getValue();
    }
    //qDebug() << "Mixer: getValue():" << value;
    return value;
}

// Note on
void Mixer::on(float frequency, float velocity, int channel){
    qDebug() << "Mixer on" << frequency << channel;
    instruments[channel]->on(frequency,velocity);
}


//Note off
void Mixer::off(float frequency, float channel){
    qDebug() << "Mixer off" << frequency << channel;
    instruments[channel]->off(frequency);
}
