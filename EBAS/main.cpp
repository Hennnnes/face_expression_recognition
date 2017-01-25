#include "videoplayer.h"
#include <QApplication>
#include <QDebug>
#include <QThread>
#include "audiocontroller.h"
#include "soundsource.h"
#include "audioengine/audioplayer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoPlayer w;
    w.show();
    a.thread()->setPriority(QThread::HighestPriority);
    qDebug() << "GUI Thread ID:" << a.thread()->currentThreadId();


    //***********************************************************************************************
    //diese Schritte werden beim Programmstart durchgeführt
    //sie erzeugen alle Grundelemente der Audiowiedergabe
    //***********************************************************************************************

    //SoundSource wird im MainThread erzeugt
    SoundSource ss;

    //AudioPlayer wird im MainThread erzeugt
    AudioPlayer ap(&w, 1024);
    ap.setAudioSource(&ss);


    AudioController ac;
    w.setAudioController(&ac);

    ss.setAudioController(&ac);
    ss.start();
    ap.start();

    return a.exec();
}
