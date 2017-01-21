#include "soundmodul.h"
#include <QDebug>

// Constructor
SoundModul::SoundModul(QObject* parent)
    :audioPlayer(parent,1024)
{

}


// Returns a pointer for the mixer
Mixer* SoundModul::getMixer(){
    return soundSource.getMixer();
}

// Returns a pointer for the MidiMangaer
MidiManager* SoundModul::getMidiManager(){
    return &midiManager;
}

// initializes the audio and starts the playback
void SoundModul::initializeAudio(){
    audioPlayer.setAudioSource(&soundSource);
    audioPlayer.start();
    midiManager.setMixer(this->getMixer());
    soundSource.setMidiManager(this->getMidiManager());
    qDebug() << "Start erfolgreich";
}
