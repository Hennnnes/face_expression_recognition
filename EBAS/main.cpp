#include "videoplayer.h"
#include <QApplication>
#include "audiowindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AudioWindow audiowindow;
    VideoPlayer w;
    w.show();

    return a.exec();
}
