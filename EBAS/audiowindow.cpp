#include "audiowindow.h"
#include "QDebug"

AudioWindow::AudioWindow(QWidget *parent)
    :QMainWindow(parent)
      ,thread(new AudioThread(parent))
{
    thread->run();
    qDebug() << "Window";
}
AudioWindow::~AudioWindow(){

}

void AudioWindow::setEmotion(int emotion){
    //thread->run();
}
