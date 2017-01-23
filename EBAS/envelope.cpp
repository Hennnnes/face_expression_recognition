#include "envelope.h"
#include <math.h>

const float MIN_DB = -180; // defines the minimum level
const float MIN_GAIN = pow(10, MIN_DB/20); // defines the minimum gain

// converts dB into a gain value
inline float dB2gain(float dB){
    return pow(10, dB/20);
}

// converts a gain value into dB
inline float gain2db(float gain){
    return 20 * log(gain);
}



// Constructor
Envelope::Envelope(AdditiveOscillator *aosc):
    sampleRate(0), gain(0), state(OFF), attackSeconds(0)
  , decaySeconds(0), releaseSeconds(0), sustain_dB(MIN_DB)
  , sustain_gain(MIN_GAIN), decay_dB_per_sec(0), decaying(false)
  , gainChange(0), aosc(aosc)
{
}

// Destructor
Envelope::~Envelope(){

}



// initializes the Envelope
void Envelope::initialize(int sampleRate){
    this->sampleRate = sampleRate;
}


// sets the attack length
void Envelope::setAttackSeconds(float seconds){
    this->attackSeconds = seconds;
}

// sets the decay length
void Envelope::setDecaySeconds(float seconds){
    this->decaySeconds = seconds;
}

// sets the release length
void Envelope::setReleaseSeconds(float seconds){
    this->releaseSeconds = seconds;
}

// sets the sustain level
void Envelope::setSustainLevel(float dB){
    this->sustain_dB = dB;
    this->sustain_gain = dB2gain(dB);
}

// sets the decay loss per second
void Envelope::setDecayLoss(float dB_per_second){
    this->decay_dB_per_sec = dB_per_second;
}

// sets wether the envelope is continously decaying or
// sustaining a constant level
void Envelope::setDecaying(bool decaying){
    this->decaying = decaying;
}



// applies the envelope on the input sample
float Envelope::process(float input){
    // switches the state to DECAY when maximum gain is reached
    if(state == ATTACK && gain >= 1){
        setState(DECAY);
    }
    // switches the state to SUSTAIN when DECAY is finished
    if(state == DECAY && gain < sustain_gain){
        setState(SUSTAIN);
    }
    // switches the state to OFF when gain reaches the MIN_GAIN
    if(state == RELEASE && gain < MIN_GAIN){
        aosc->setFrequency(0);
        setState(OFF);
    }

    gain *= gainChange; // updates the ADSR gain factor
    return gain * input; // processes the input sample
}

// triggers the envelope to start
void Envelope::on(){
    this->setState(ATTACK);
}

// triggers the envelope to fade out
void Envelope::off(){
    this->setState(RELEASE);
}

// returns false if the Envelope is currently used
// of true if its ready to play the next note
bool Envelope::isAvailable(){
    if(state == OFF){
        return true;
    }else{
        return false;
    }
}



// updates the current state of the Envelope
void Envelope::setState(State state){
    this->state = state;
    //avoid division by zero
    if(state == ATTACK && attackSeconds == 0){
        setState(DECAY);
    }
    else if(state == DECAY && decaySeconds == 0){
        setState(SUSTAIN);
    }
    else if(state == RELEASE && releaseSeconds == 0){
        setState(OFF);
    }
    else{
        // sets gain to zero when the state is OFF
        if(state == OFF){
            gain = 0;
        }
        // updates the gainChange variable and sets gain to MIN_GAIN
        if(state == ATTACK){
            float gainChange_dB = fabs(MIN_DB) / (attackSeconds * sampleRate);
            gainChange = dB2gain(gainChange_dB);
            gain = MIN_GAIN;
        }
        // updates the gainChange variable and sets gain to one
        if(state == DECAY){
            gain = 1;
            float gainChange_dB = fabs(sustain_dB) / (decaySeconds * sampleRate);
            gainChange = 1 / dB2gain(gainChange_dB);
        }
        // sets gain to sustain_gain and gainChange to one
        // for the sustained constant level
        if(state == SUSTAIN && decaying == false){
            gain = sustain_gain;
            gainChange = 1;
        }
        // sets the gainChange for the continously decaying envelope
        if(state == SUSTAIN && decaying == true){
            float gainChange_dB = fabs(decay_dB_per_sec) / sampleRate;
            gainChange = 1 / dB2gain(gainChange_dB);
        }
        // updates the gainChange variable for RELEASE
        if(state == RELEASE){
            float gainChange_dB = fabs(gain2db(gain) - MIN_DB) / (releaseSeconds * sampleRate);
            gainChange = 1 / dB2gain(gainChange_dB);
        }

    }
}




