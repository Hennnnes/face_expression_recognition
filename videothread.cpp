#include "videothread.h"
#include <QDebug>

#include "videocapturer.h"

videoThread::videoThread()
{

}


void videoThread::run() {
    VideoCapturer capturer;
    // capturer.start();

    for (int i = 0; i < 100; ++i) {
        qDebug() << i;
    }
}
