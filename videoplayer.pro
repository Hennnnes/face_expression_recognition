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
    copyprocessor.cpp \
    ../../../../../../../../dlib-19.2/dlib/all/source.cpp

HEADERS  += videoplayer.h \
    copyprocessor.h

FORMS    += videoplayer.ui

include(../opencv/videoengine.pri)

# The following lines tells Qmake to  use pkg-config for opencv
QT_CONFIG -= no-pkg-config
CONFIG  += link_pkgconfig
PKGCONFIG += opencv

INCLUDEPATH += /Users/hennesroemmer/dlib-19.2
LIBS += -pthread
CONFIG += link_pkgconfig
PKGCONFIG += x11

DISTFILES += \
    shape_predictor_68_face_landmarks.dat
