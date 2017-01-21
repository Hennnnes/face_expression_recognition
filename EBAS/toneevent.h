#ifndef TONEEVENT_H
#define TONEEVENT_H


class ToneEvent
{
public:
    ToneEvent(float time, float frequency, float velocity, int channel);

    float getTime();
    float getFrequency();
    float getVelocity();
    int getChannel();

private:
    float time;
    float frequency;
    float velocity;
    int channel;

};

#endif // TONEEVENT_H
