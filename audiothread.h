#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QObject>
#include <QThread>
#include "soundmodul.h"


class AudioThread: public QThread
{
public:
    AudioThread(QObject* parent);
    void run();

private:
    SoundModul* sm;
};

#endif // AUDIOTHREAD_H
