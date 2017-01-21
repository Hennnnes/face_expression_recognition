#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H

#include "audioengine/audiosource.h"
#include "mixer.h"
#include "audiocontroller.h"
//#include "midimanager.h"


class SoundSource: public AudioSource
{

public:
    SoundSource();
    virtual const QAudioFormat& format() const;
    virtual qint64 read(float **buffer, qint64 numFrames);
    virtual void start();
    virtual void stop();
    void setMixer(Mixer* mixer);
    void setAudioController(AudioController* ac);
    int getSampleRate();
    //Mixer* getMixer();
    //void setMidiManager(MidiManager* midiManager);

private:
    //MidiManager* midiManager;
    Mixer *mixer;
    AudioController *ac;
    float createSample();
    QAudioFormat audioFormat;

};

#endif // SOUNDSOURCE_H
