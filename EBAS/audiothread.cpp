#include "audiothread.h"

#include <QDebug>

AudioThread::AudioThread()
{

    //this->setPriority(QThread::TimeCriticalPriority)
    qDebug() << "AudioThread initialized";
}

AudioThread::~AudioThread(){
    qDebug() << "~AudioThread";
}

void AudioThread::run(){
    this->setPriority(QThread::HighPriority);
    qDebug() << "AudioThread started:" << thread()->currentThreadId();
    exec();
}
