#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "toneevent.h"
#include "mixer.h"
#include <vector>
#include <ctime>
#include <QObject>

class Sequencer: public QObject
{
    Q_OBJECT
public:
    Sequencer();
    ~Sequencer();

    void dumpEvent(ToneEvent *te);
    void setMixer(Mixer* m);
    void setEmotion(int emotion);
    void start();
    void update();
    void loadNextEvent();
    bool isBusy();

private:
    bool busy;
    Mixer* m;
    int emotion;
    int index;
    double startTime;
    double duration;
    ToneEvent *currentEvent;

    std::vector<ToneEvent*> neutral;
    std::vector<ToneEvent*> happy;
    std::vector<ToneEvent*> surprised;
    std::vector<ToneEvent*> sad;

signals:
    void on(float freq, float velocity, int channel);
    void off(float freq, int channel);
};

#endif // SEQUENCER_H
