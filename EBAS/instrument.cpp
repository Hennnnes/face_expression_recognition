#include "instrument.h"
#include <QDebug>


// Constructor
Instrument::Instrument():
    available(false), sampleRate(0), type(PIANO),
    num_osc(0)
{}

// Destructor
Instrument::~Instrument(){
    for(int i = 0; i < osc.size(); i++){
        delete osc[i];
        delete env[i];
    }
}

// initializes the Instrument
void Instrument::initialize(int sampleRate, int num_osc){
    this->sampleRate = sampleRate;
    this->set_num_osc(num_osc);
    qDebug() << "Instrument initialized";
}

// sets the Type of the Instrument
void Instrument::setInstrument(int type){
    this->type = PIANO;
}

// sets the amount of Oscillators and initializes
// them and the corresponding Envelopes
void Instrument::set_num_osc(int num){
    this->num_osc = num;
    // deletes the old Oscillators and Envelopes
    for(int i = 0; i < osc.size(); i++){
        delete osc[i];
        delete env[i];
    }
    osc.resize(num_osc);
    env.resize(num_osc);
    // creates the new Oscillators and Envelopes
    for(int i = 0; i < num_osc; i++){
        osc[i] = new AdditiveOscillator();
        env[i] = new Envelope();
        osc[i]->initialize(sampleRate);
        env[i]->initialize(sampleRate);
        env[i]->setAttackSeconds(.05);
        env[i]->setDecaySeconds(.3);
        env[i]->setReleaseSeconds(1.5);
        env[i]->setSustainLevel(-20);
        env[i]->setDecayLoss(-10);
        env[i]->setDecaying(true);
        std::vector<float> overtones(9);
        overtones[0] = 1;
        overtones[1] = 2.0021;
        overtones[2] = 3.01;
        overtones[3] = 4.0226;
        overtones[4] = 5.0462;
        overtones[5] = 6.0804;
        overtones[6] = 7.1266;
        overtones[7] = 8.185;
        overtones[8] = 9.2738;
//        overtones[9] = 10.093;
//        overtones[10] = 10.3726;
//        overtones[11] = 11.1261;
//        overtones[12] = 11.4882;
//        overtones[13] = 12.6180;

        std::vector<float> overtoneLevels(9);
        overtoneLevels[0] = 0;
        overtoneLevels[1] = -10.9858;
        overtoneLevels[2] = -24.3062;
        overtoneLevels[3] = -28.8732;
        overtoneLevels[4] = -34.1533;
        overtoneLevels[5] = -35.6090;
        overtoneLevels[6] = -38.8853;
        overtoneLevels[7] = -55.0847;
        overtoneLevels[8] = -60.6511;
//        overtoneLevels[9] = -86.1601;
//        overtoneLevels[10] = -77.9193;
//        overtoneLevels[11] = -81.2649;
//        overtoneLevels[12] = -74.2643;
//        overtoneLevels[13] = -76.9091;

        osc[i]->setOvertones(overtones);
        osc[i]->setOvertoneLevels(overtoneLevels);
        osc[i]->setGain(.5);
    }
    available = true; // sets the availability to true
}

// returns the amount of Oscillators / available voices
int Instrument::get_num_osc(){
    return num_osc;
}

// returns true if the Instrument is ready to play a new note
bool Instrument::isAvailable(){
    available = false;
    for(int i = 0; i < env.size(); i++){
        available |= env[i]->isAvailable();
    }
    return available;
}



// adds the samples of the single voices and returns the sum
float Instrument::getValue(){
    float sample = 0;
    for(int i = 0; i < osc.size(); i++){
        float oscSample = osc[i]->getValue();
        sample += env[i]->process(oscSample);
    }
    //qDebug() << "Instrument: getValue():" << sample;
    return sample;
}

// triggers a new note to play if an Oscillator is available
void Instrument::on(float frequency, float velocity){
    if(velocity == 0){
        this -> off(frequency);
    }
    if(this->isAvailable()){
        for(int i = 0; i < osc.size(); i++){
            if(frequency == osc[i]->getFrequency()){
                return;
            }
        }
        int k = indexOfAvailableOsc();
        if(k != -1 && env[k]->isAvailable() == true){
            osc[k]->setFrequency(frequency);
            env[k]->on();
        }
        qDebug() << "Instrument on" << frequency << k;
    }
}

// triggers the note with the frequency to stop playing
void Instrument::off(float frequency){
    for(int i = 0; i < osc.size(); i++){
        if(frequency == osc[i]->getFrequency() || frequency == 0){
            osc[i]->setFrequency(0);
            env[i]->off();
            qDebug() << "Instrument off" << frequency << i;
        }
    }
    this->isAvailable();
}


// returns the index of the first available Oscillator
// returns -1 if no Oscillator is available
int Instrument::indexOfAvailableOsc(){
    for(int i = 0; i < env.size(); i++){
        if(env[i]->isAvailable() == true){
            return i;
        }
    }
    return -1;
}











