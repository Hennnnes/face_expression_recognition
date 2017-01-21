#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H

#include "audioengine/audiosource.h"
#include "mixer.h"
#include "midimanager.h"


class SoundSource: public AudioSource
{

public:
    SoundSource();
    virtual const QAudioFormat& format() const;
    virtual qint64 read(float **buffer, qint64 numFrames);
    virtual void start();
    virtual void stop();
    Mixer* getMixer();
    void setMidiManager(MidiManager* midiManager);

private:
    MidiManager* midiManager;
    float createSample();
    QAudioFormat audioFormat;
    Mixer mixer;

};

#endif // SOUNDSOURCE_H
