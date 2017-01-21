#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QThread>
#include <QObject>

class AudioThread: public QThread
{
public:
    AudioThread();
    ~AudioThread();
    void run();
};

#endif // AUDIOTHREAD_H
