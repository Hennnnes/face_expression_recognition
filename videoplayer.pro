#-------------------------------------------------
#
# Project created by QtCreator 2014-07-15T19:38:24
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = VideoPlayer
TEMPLATE = app


SOURCES += main.cpp\
        videoplayer.cpp \
        facerecognizer.cpp \
        videocapturer.cpp \
        copyprocessor.cpp \
        videothread.cpp

HEADERS  += videoplayer.h \
            facerecognizer.h \
            videocapturer.h \
            copyprocessor.h \
            videothread.h

FORMS    += videoplayer.ui


include(../opencv/videoengine.pri)

DISTFILES += \
    shape_predictor_68_face_landmarks.dat


## Link Dlib Stuff
macx {
    # path to dlib folder
    INCLUDEPATH += /Users/hennesroemmer/dlib-19.2
    LIBS += -pthread
    CONFIG += link_pkgconfig
    PKGCONFIG += x11

    # link source.cpp inside dlib/all/
    SOURCES +=  ../../../../../../../../dlib-19.2/dlib/all/source.cpp
}
