#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMainWindow>
#include <QImage>
#include "videoengine.h"
#include "dlibprocessor.h"

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

private slots:
    void on_actionVideodatei_ffnen_triggered();
    void on_actionKamera_ffnen_triggered();
    void on_actionPlay_triggered();
private:
    Ui::VideoPlayer *ui;
    VideoEngine *videoThread;
    Dlibprocessor *dlibprocessor;
};

#endif // VIDEOPLAYER_H
