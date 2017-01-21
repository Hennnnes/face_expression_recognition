#ifndef TONEEVENT_H
#define TONEEVENT_H


class ToneEvent
{
public:
    ToneEvent(int time, float frequency, float velocity, int channel);

    int getTime();
    float getFrequency();
    float getVelocity();
    int getChannel();

private:
    int time;
    float frequency;
    float velocity;
    int channel;

};

#endif // TONEEVENT_H
