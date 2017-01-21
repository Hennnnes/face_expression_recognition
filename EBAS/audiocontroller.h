#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include <QObject>
#include "audiothread.h"
#include "audiomodule.h"
#include "mixer.h"
#include "sequencer.h"

class AudioController: public QObject
{
    Q_OBJECT
public:
    AudioController();
    ~AudioController();

    float getValue();
    bool isBusy();
    Mixer* getMixer();



private:
    AudioThread at;
    AudioModule *am;


public slots:
    void test();
    void initialize();
    void setEmotion(int emotion);
    void startPlayback();
    void playTone(float frequency);
    void on(float freq, float velocity, int channel);
    void off(float freq, int channel);

signals:
    void testSig1();
    void initSig();
    void updateSig();
    void setEmotionSig(int emotion);
    void playbackCue();
    void tone(float frequency);
    void updateSeq();
};

#endif // AUDIOCONTROLLER_H
