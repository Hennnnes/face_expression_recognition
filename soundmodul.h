#ifndef SOUNDMODUL_H
#define SOUNDMODUL_H

#include "audioengine/audioplayer.h"
#include "soundsource.h"
#include "midimanager.h"
#include <QObject>


class SoundModul: public QObject
{
    Q_OBJECT

public:
    SoundModul();
    Mixer* getMixer();
    MidiManager* getMidiManager();
    void initializeAudio();
private:
    SoundSource soundSource;
    AudioPlayer audioPlayer;
    MidiManager midiManager;
};

#endif // SOUNDMODUL_H
