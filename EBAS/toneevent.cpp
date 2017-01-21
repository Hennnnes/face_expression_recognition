#include "toneevent.h"

ToneEvent::ToneEvent(float time,float frequency, float velocity, int channel):
    time(time),
    frequency(frequency),
    velocity(velocity),
    channel(channel)
{

}

float ToneEvent::getTime(){
    return time;
}

float ToneEvent::getFrequency(){
    return frequency;
}

float ToneEvent::getVelocity(){
    return velocity;
}

int ToneEvent::getChannel(){
    return channel;
}

