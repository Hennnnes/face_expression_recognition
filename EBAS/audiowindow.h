#ifndef AUDIOWINDOW_H
#define AUDIOWINDOW_H

#include <QMainWindow>
#include "audiothread.h"

class AudioWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit AudioWindow(QWidget *parent = 0);
    ~AudioWindow();
    void setEmotion(int emotion);
private:
    AudioThread* thread;
};

#endif // AUDIOWINDOW_H
