#include "toneevent.h"

ToneEvent::ToneEvent(int time,float frequency, float velocity, int channel):
    time(time),
    frequency(frequency),
    velocity(velocity),
    channel(channel)
{

}

int ToneEvent::getTime(){
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

