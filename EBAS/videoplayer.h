#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMainWindow>
#include <QImage>
#include "videoengine.h"
#include "dlibprocessor.h"
#include "audiocontroller.h"

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();
    void setAudioController(AudioController *ac);

private slots:
    void on_actionPlay_triggered();
private:
    Ui::VideoPlayer *ui;
    VideoEngine *videoThread;
    Dlibprocessor *dlibprocessor;
    AudioController *ac;
};

#endif // VIDEOPLAYER_H
