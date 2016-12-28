#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include <QThread>
#include "videocapturer.h"

class videoThread : public QThread
{
public:
    videoThread();

    // overwrite thread method
    void run();
};

#endif // VIDEOTHREAD_H
