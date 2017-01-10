#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H
#include <QThread>
#include "soundmodul.h"


class AudioThread:public QThread
{
public:
    explicit AudioThread();
    void run();
    void setEmotion(int emotion);
    bool getPlaying();
    void setPlaying(bool playing);
private:
    SoundModul* soundModul;
    int emotion;
    bool playing;
};

#endif // AUDIOTHREAD_H
