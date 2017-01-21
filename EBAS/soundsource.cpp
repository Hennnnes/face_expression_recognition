#include "soundsource.h"
#include "audioengine/audiosource.h"

#include <iostream>
#include <QDebug>

// Constructor
SoundSource::SoundSource()
{
    audioFormat.setCodec("audio/pcm"); // Codec gets set to linear PCM >>> default: "audio/pcm"
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);  // Byte Order >>> default: QAudioFormat::LittleEndian
    audioFormat.setChannelCount(2); // Amount of audio channels gets set >>> default: 2
    audioFormat.setSampleSize(32);  // Bits per Sample >>> default: 32
    audioFormat.setSampleType(QAudioFormat::Float); // Audio sample format gets set to floating point >>> default: QAudioFormat::Float
    audioFormat.setSampleRate(44100); // Sample Rate gets set >>> default: 44100

    qDebug() << "SoundSource initialized";
}

// Starts the audio output
void SoundSource::start(){
    //mixer.initialize(audioFormat.sampleRate(), 4);
}

void SoundSource::setMixer(Mixer *mixer){
    this->mixer = mixer;
    qDebug() << "SoundSource: set Mixer";
}

void SoundSource::setAudioController(AudioController *ac){
    this->ac = ac;
    qDebug() << "SoundSource: set AudioController";
}

// Returns the QAudioFormat
const QAudioFormat& SoundSource::format() const{
    return audioFormat;
}

//Sets the MidiManager
//void SoundSource::setMidiManager(MidiManager *midiManager){
    //this->midiManager = midiManager;
//}

// Returns a pointer for the mixer
//Mixer* SoundSource::getMixer(){
//    return 0;//&mixer;
//}

// Creates the next sample
float SoundSource::createSample(){
    float sample = 0;
    sample = ac->getValue();
    //midiManager->update();
    //float sample = mixer.getValue();
    //qDebug() << "SoundSource Sample:" << sample;
    return sample;
}

// Reads the next samples into the buffers of the audio channels
qint64 SoundSource::read(float **buffer, qint64 numFrames){
    // get audio data for left channel
    for(int i = 0; i < numFrames; i++){
        buffer[0][i] = createSample();
    }

    //copy to other channels
    for(int c = 0; c < audioFormat.channelCount(); c++){
        for(int i = 0; i < numFrames; i++){
            buffer[c][i] = buffer[0][i];
        }
    }
    return numFrames;
}

// Stops the audio output
void SoundSource::stop(){
    qDebug() << "SoundSource: stop()";
}

// Returns the sampleRate
int SoundSource::getSampleRate(){
    return audioFormat.sampleRate();
}




