#include "audiocontroller.h"

#include <QDebug>

AudioController::AudioController()
{
    am = new AudioModule;
    am->moveToThread(&at);
    connect(am->getSequencer(), &Sequencer::on, this, &AudioController::on);
    connect(am->getSequencer(), &Sequencer::off, this, &AudioController::off);
    connect(&at, &QThread::finished, am, &QObject::deleteLater);
    connect(this, &AudioController::testSig1, am, &AudioModule::test);
    connect(this, &AudioController::initSig, am, &AudioModule::initialize);
    connect(this, &AudioController::updateSig, am, &AudioModule::update);
    connect(this, &AudioController::setEmotionSig, am, &AudioModule::setEmotion);
    connect(this, &AudioController::tone, am, &AudioModule::playTone);
    connect(this, &AudioController::updateSeq, am, &AudioModule::updateSequencer);
    test();
    am->test();
    at.start();
    initialize();
    startPlayback();
    qDebug() << "AudioController init";
}

AudioController::~AudioController(){
    at.quit();
    at.wait();
    qDebug() << "~AudioController";
}

void AudioController::test(){
    qDebug() << "test!";
    emit testSig1();
}

void AudioController::initialize(){
    qDebug() << "AC: init";
    emit initSig();
}

void AudioController::setEmotion(int emotion){
    //qDebug() << "AC: setEmotion";
    emit setEmotionSig(emotion);
}

void AudioController::startPlayback(){
    emit playbackCue();
}

void AudioController::playTone(float frequency){
    emit tone(frequency);
}

float AudioController::getValue(){
    //qDebug() << "AC: getValue():" << nextSample;
    //emit updateSig();
    if(isBusy()){
        float value = getMixer()->getValue();
        emit updateSeq();
        //am->updateSequencer();
        return value;
    }else{
        return 0.;
    }

}

Mixer* AudioController::getMixer(){
    return am->getMixer();
}

void AudioController::on(float freq, float velocity, int channel){
    am->getMixer()->on(freq, velocity, channel);
}

void AudioController::off(float freq, int channel){
    am->getMixer()->off(freq, channel);
}

bool AudioController::isBusy(){
    return am->getSequencer()->isBusy();
}


