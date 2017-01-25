#-------------------------------------------------
#
# Project created by QtCreator 2014-07-15T19:38:24
#
#-------------------------------------------------

QT       += core gui widgets multimedia

TARGET = VideoPlayer
TEMPLATE = app


SOURCES += main.cpp\
        videoplayer.cpp \
    dlibprocessor.cpp \
    facerecognizer.cpp \
    additiveoscillator.cpp \
    audiocontroller.cpp \
    audiomodule.cpp \
    audiothread.cpp \
    envelope.cpp \
    instrument.cpp \
    mixer.cpp \
    soundsource.cpp \
    toneevent.cpp \
    sequencer.cpp


HEADERS  += videoplayer.h \
    dlibprocessor.h \
    facerecognizer.h \
    additiveoscillator.h \
    audiocontroller.h \
    audiomodule.h \
    audiothread.h \
    envelope.h \
    instrument.h \
    mixer.h \
    soundsource.h \
    toneevent.h \
    sequencer.h

FORMS    += videoplayer.ui


include(../opencv/videoengine.pri)
include(./audioengine/AudioPlayer.pri)

DISTFILES += shape_predictor_68_face_landmarks.dat


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


win32 {
#  für Windows muss die Umgebungsvariable OPENCV_DIR gesetzt sein
#  auf den Pfad der OpenCV-Installation
#  Beispiel: C:\opencv\opencv-3.1.0\opencv\build\x64\vc14

    INCLUDEPATH += $$(OPENCV_DIR)\..\..\include
    LIBS += -L$$(OPENCV_DIR)\lib
    Release:LIBS +=  -lopencv_world310
    Debug:LIBS +=  -lopencv_world310d

    INCLUDEPATH += C:\Users\Raoul\Desktop\dlib-19.2\
    LIBS+= -lgdi32 -lcomctl32 -luser32 -lwinmm -lws2_32

    SOURCES +=     C:\Users\Raoul\Desktop\dlib-19.2\dlib\all\source.cpp

}
