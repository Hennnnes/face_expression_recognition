#ifndef AUDIOMODULE_H
#define AUDIOMODULE_H

#include <QObject>
#include <QThread>

#include "mixer.h"
#include "sequencer.h"

class AudioModule: public QObject
{
    Q_OBJECT
public:
    AudioModule();
    ~AudioModule();
    void initialize();
    Mixer* getMixer();
    Sequencer* getSequencer();
    //void updateSequencer();

private:
    Mixer *m;
    Sequencer s;

    int sampleRate;
    float lastFreq;

public slots:
    void test();
    void update();
    void setEmotion(int emotion);
    void startPlayback();
    void playTone(float frequency);
    void updateSequencer();

signals:
    void testSig();
    void updated(float sample);
};

#endif // AUDIOMODULE_H
