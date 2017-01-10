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
#Soundstuff
    soundmodul.cpp \
    soundsource.cpp \
    mixer.cpp \
    additiveoscillator.cpp \
    envelope.cpp \
    instrument.cpp \
    jdks_midi_lib/jdksmidi_advancedsequencer.cpp \
    jdks_midi_lib/jdksmidi_driver.cpp \
    jdks_midi_lib/jdksmidi_driverdump.cpp \
    jdks_midi_lib/jdksmidi_edittrack.cpp \
    jdks_midi_lib/jdksmidi_file.cpp \
    jdks_midi_lib/jdksmidi_fileread.cpp \
    jdks_midi_lib/jdksmidi_filereadmultitrack.cpp \
    jdks_midi_lib/jdksmidi_fileshow.cpp \
    jdks_midi_lib/jdksmidi_filewrite.cpp \
    jdks_midi_lib/jdksmidi_filewritemultitrack.cpp \
    jdks_midi_lib/jdksmidi_keysig.cpp \
    jdks_midi_lib/jdksmidi_manager.cpp \
    jdks_midi_lib/jdksmidi_matrix.cpp \
    jdks_midi_lib/jdksmidi_midi.cpp \
    jdks_midi_lib/jdksmidi_msg.cpp \
    jdks_midi_lib/jdksmidi_multitrack.cpp \
    jdks_midi_lib/jdksmidi_parser.cpp \
    jdks_midi_lib/jdksmidi_process.cpp \
    jdks_midi_lib/jdksmidi_queue.cpp \
    jdks_midi_lib/jdksmidi_sequencer.cpp \
    jdks_midi_lib/jdksmidi_showcontrol.cpp \
    jdks_midi_lib/jdksmidi_showcontrolhandler.cpp \
    jdks_midi_lib/jdksmidi_smpte.cpp \
    jdks_midi_lib/jdksmidi_sysex.cpp \
    jdks_midi_lib/jdksmidi_tempo.cpp \
    jdks_midi_lib/jdksmidi_tick.cpp \
    jdks_midi_lib/jdksmidi_track.cpp \
    jdks_midi_lib/jdksmidi_utils.cpp \
    audiothread.cpp \
    midimanager.cpp


HEADERS  += videoplayer.h \
    dlibprocessor.h \
    facerecognizer.h \
#Soundstuff
    soundmodul.h \
    soundsource.h \
    mixer.h \
    additiveoscillator.h \
    envelope.h \
    instrument.h \
    jdks_midi_lib/advancedsequencer.h \
    jdks_midi_lib/driver.h \
    jdks_midi_lib/driverdump.h \
    jdks_midi_lib/driverwin32.h \
    jdks_midi_lib/edittrack.h \
    jdks_midi_lib/file.h \
    jdks_midi_lib/fileread.h \
    jdks_midi_lib/filereadmultitrack.h \
    jdks_midi_lib/fileshow.h \
    jdks_midi_lib/filewrite.h \
    jdks_midi_lib/filewritemultitrack.h \
    jdks_midi_lib/keysig.h \
    jdks_midi_lib/manager.h \
    jdks_midi_lib/matrix.h \
    jdks_midi_lib/midi.h \
    jdks_midi_lib/msg.h \
    jdks_midi_lib/multitrack.h \
    jdks_midi_lib/parser.h \
    jdks_midi_lib/process.h \
    jdks_midi_lib/queue.h \
    jdks_midi_lib/sequencer.h \
    jdks_midi_lib/showcontrol.h \
    jdks_midi_lib/showcontrolhandler.h \
    jdks_midi_lib/smpte.h \
    jdks_midi_lib/song.h \
    jdks_midi_lib/sysex.h \
    jdks_midi_lib/tempo.h \
    midimanager.h \
    jdks_midi_lib/tick.h \
    jdks_midi_lib/track.h \
    jdks_midi_lib/utils.h \
    jdks_midi_lib/world.h \
    audiothread.h

FORMS    += videoplayer.ui


include(../opencv/videoengine.pri)
include(./audioEngine/audioplayer.pri)


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

    INCLUDEPATH += C:\Users\Raoul\Desktop\dlib-19.2
    LIBS+= -lgdi32 -lcomctl32 -luser32 -lwinmm -lws2_32

    SOURCES +=     ../../Desktop/dlib-19.2/dlib/all/source.cpp

}
