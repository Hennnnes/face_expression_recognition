#include "audiothread.h"

#include <iostream>

AudioThread::AudioThread(): emotion(0), playing(false)
{

}

void AudioThread::run(){
    SoundModul *soundModul = new SoundModul();
    soundModul->initializeAudio();
    std::cout << "hallo" << std::endl;

}

void AudioThread::setEmotion(int emotion){
    soundModul->getMidiManager()->setEmotion(emotion);
    setPlaying(true);
}

bool AudioThread::getPlaying() {
    return playing;
}

void AudioThread::setPlaying(bool playing) {
    this->playing = playing;
}
