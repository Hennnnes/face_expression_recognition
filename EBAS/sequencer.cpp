#include "sequencer.h"

#include <QDebug>

Sequencer::Sequencer()
    :startTime(0),
      index(0),
      emotion(0),
      busy(false)
{
    //NEUTRAL
    neutral.resize(15);
    neutral[0] = new ToneEvent(0.,330,1,0);
    neutral[1] = new ToneEvent(.74,330,0,0);
    neutral[2] = new ToneEvent(.75,220,1,0);
    neutral[3] = new ToneEvent(.9,220,0,0);
    neutral[4] = new ToneEvent(1.,262,1,0);
    neutral[5] = new ToneEvent(1.2,262,0,0);
    neutral[6] = new ToneEvent(1.25,294,1,0);
    neutral[7] = new ToneEvent(1.4,294,0,0);
    neutral[8] = new ToneEvent(1.5,220,1,0);
    neutral[9] = new ToneEvent(1.9,220,0,0);
    neutral[10] = new ToneEvent(2.,196,1,0);
    neutral[11] = new ToneEvent(2.2,196,0,0);
    neutral[12] = new ToneEvent(2.25,220,1,0);
    neutral[13] = new ToneEvent(3.,220,0,0);
    neutral[14] = new ToneEvent(6,0,0,0);

    //HAPPY
    happy.resize(7);
    happy[0] = new ToneEvent(0,262,1,0);
    happy[1] = new ToneEvent(.6,262,0,0);
    happy[2] = new ToneEvent(.5,330,1,0);
    happy[3] = new ToneEvent(1.1,330,0,0);
    happy[4] = new ToneEvent(1.,392,1,0);
    happy[5] = new ToneEvent(2.,392,0,0);
    happy[6] = new ToneEvent(7,0,0,0);

    //SAD
    sad.resize(3);
    sad[0] = new ToneEvent(0,880,1,0);
    sad[1] = new ToneEvent(1.,880,0,0);
    sad[2] = new ToneEvent(7,0,0,0);

    //SURPRISED
    surprised.resize(9);
    surprised[0] = new ToneEvent(0,440,1,0);
    surprised[1] = new ToneEvent(.9,440,0,0);
    surprised[2] = new ToneEvent(1,660,1,0);
    surprised[3] = new ToneEvent(1.9,660,0,0);
    surprised[4] = new ToneEvent(2.,1320,1,0);
    surprised[5] = new ToneEvent(2.5,1320,0,0);
    surprised[6] = new ToneEvent(3,880,1,0);
    surprised[7] = new ToneEvent(3.5,880,0,0);
    surprised[8] = new ToneEvent(7,0,0,0);

    qDebug() << "Sequencer initialized";
}

Sequencer::~Sequencer(){
    qDebug() << "~Sequencer";
}


void Sequencer::setMixer(Mixer *m){
    this->m = m;
}

void Sequencer::setEmotion(int emotion){
    if(!busy){
        this->emotion = emotion;
        start();
    }else{
        //qDebug() << "Emotion already set!";
    }
}

void Sequencer::start(){
    if(!busy){
        busy = true;
        startTime = std::clock() / (double) CLOCKS_PER_SEC;
        index = 0;
        qDebug() << "Playback started";
        qDebug() << "busy =" << busy << "startTime =" << startTime;
        loadNextEvent();
        //update();
    }
}

void Sequencer::update(){
    //qDebug() << "Sequencer update()";
    if(busy){
        duration = (std::clock() / (double) CLOCKS_PER_SEC) - startTime ;
        //qDebug() << "Duration:" << duration;
        if(duration >= currentEvent->getTime()){
            dumpEvent(currentEvent);
        }
    }
}

void Sequencer::loadNextEvent(){
    switch (emotion){
    //NEUTRAL
    case 0:
        if(index < neutral.size()){
            currentEvent = neutral[index];
            //qDebug() << "Event" << index << "set";
        }else{
            busy = false;
            qDebug() << "Playback finished! busy =" << busy ;
        }
        break;
    //HAPPY
    case 1:
        if(index < happy.size()){
            //qDebug() << "Event" << index << "set";
            currentEvent = happy[index];
        }else{
            busy = false;
            qDebug() << "Playback finished! busy =" << busy ;
        }
        break;
    //SAD
    case 2:
        if(index < sad.size()){
            //qDebug() << "Event" << index << "set";
            currentEvent = sad[index];
        }else{
            busy = false;
            qDebug() << "Playback finished! busy =" << busy ;
        }
        break;
    //SURPRISED
    case 3:
        if(index < surprised.size()){
            //qDebug() << "Event" << index << "set";
            currentEvent = surprised[index];
        }else{
            busy = false;
            qDebug() << "Playback finished! busy =" << busy ;
        }
        break;
    //
    default:
        if(index < neutral.size()){
            //qDebug() << "Event" << index << "set";
            currentEvent = neutral[index];
        }else{
            busy = false;
            qDebug() << "Playback finished! busy =" << busy ;
        }
    }
    //qDebug() << "busy" << busy;
}

void Sequencer::dumpEvent(ToneEvent *te){
    if(te->getVelocity() == 0){
        //m->off(te->getFrequency(), te->getChannel());
        index++;
        loadNextEvent();
        emit off(te->getFrequency(), te->getChannel());
        qDebug() << "Note Off:" << te->getFrequency() << te->getChannel();
    }else{
        //m->on(te->getFrequency(), te->getVelocity(), te->getChannel());
        index++;
        loadNextEvent();
        emit on(te->getFrequency(), te->getVelocity(), te->getChannel());
        qDebug() << "Note On:" << te->getFrequency() << te->getChannel() << te->getVelocity();
    }
}

bool Sequencer::isBusy(){
    return busy;
}
