#include "audiomodule.h"

#include <QDebug>

AudioModule::AudioModule()
    :sampleRate(44100),
      lastFreq(0)
{
    qDebug() << "AudioModule init";
}

AudioModule::~AudioModule(){
    delete m;
    qDebug() << "~AudioModule";
}

void AudioModule::test(){
    qDebug() << "AM: test(): ID:" << thread()->currentThreadId();
    emit testSig();
}

void AudioModule::initialize(){
    //Mixer
    m = new Mixer();
    m->initialize(sampleRate);

    qDebug() << "AM: initialize(): ID:" << thread()->currentThreadId();
}

void AudioModule::update(){
    float sample = m->getValue();
    emit updated(sample);
}

void AudioModule::setEmotion(int emotion){
    s.setEmotion(emotion);
}

void AudioModule::startPlayback(){
 //nichts
}

void AudioModule::playTone(float frequency){
    m->off(lastFreq, 0);
    this->lastFreq = frequency;
    m->on(frequency, 1., 0);
}

Mixer* AudioModule::getMixer(){
            return m;
}

void AudioModule::updateSequencer(){
    s.update();
}

Sequencer* AudioModule::getSequencer(){
    return &s;
}



