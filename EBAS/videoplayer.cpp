#include <QFileDialog>
#include "videoplayer.h"
#include "ui_videoplayer.h"

VideoPlayer::VideoPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VideoPlayer)
    , videoThread(new VideoEngine)
    , dlibprocessor(new Dlibprocessor())
{
    ui->setupUi(this);

    // setProcessor
    videoThread->setProcessor(dlibprocessor);

    connect(videoThread, &VideoEngine::sendProcessedImage,
            ui->inputFrame, &VideoWidget::setImage);
}

VideoPlayer::~VideoPlayer()
{
    delete videoThread;
    delete ui;
    delete dlibprocessor;
}

void VideoPlayer::setAudioWindow(AudioWindow *window){
    dlibprocessor->setAudioWindow(window);
}

void VideoPlayer::on_actionPlay_triggered()
{
    videoThread->openCamera();
    videoThread->start();


    // hier wird das process in einem eigenen Thread gestartet.
}
