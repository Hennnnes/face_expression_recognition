#include "audiothread.h"

AudioThread::AudioThread(QObject* parent):
    sm(new SoundModul(parent))
{

}


void AudioThread::run(){
    sm->initializeAudio();
    sm->getMidiManager()->setEmotion(0);
}
