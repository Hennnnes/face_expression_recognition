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


HEADERS  += videoplayer.h \
            copyprocessor.h \

FORMS    += videoplayer.ui


include(../opencv/videoengine.pri)

DISTFILES += \
    ../../../../../../../../Downloads/shape_predictor_68_face_landmarks.dat


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
