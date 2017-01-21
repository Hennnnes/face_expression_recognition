#include "audiothread.h"
#include "QDebug"

AudioThread::AudioThread(QObject* parent):
    sm(new SoundModul(parent))
{

}


void AudioThread::run(){
    sm->initializeAudio();
    sm->getMidiManager()->setEmotion(0);
}

void AudioThread::test() {
    qDebug() << "test";
}

void AudioThread::setEmotion(int emotion) {
    sm->getMidiManager()->setEmotion(emotion);
}
