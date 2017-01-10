#ifndef MIDIMANAGER_H
#define MIDIMANAGER_H


#ifdef WIN32
#include <windows.h>
#endif

#include "jdks_midi_lib/world.h"
#include "jdks_midi_lib/track.h"
#include "jdks_midi_lib/multitrack.h"
#include "jdks_midi_lib/filereadmultitrack.h"
#include "jdks_midi_lib/fileread.h"
#include "jdks_midi_lib/fileshow.h"
#include "jdks_midi_lib/sequencer.h"
#include "mixer.h"

#include <ctime>
#include <cmath>
#include <iostream>


using namespace std;
using namespace jdksmidi;

class MidiManager
{
public:
    MidiManager();
    ~MidiManager();
    void update();
    void initialize();
    void setMixer(Mixer* mixer);
    void setEmotion(int emotion);
private:
    Mixer* mixer;
    void DumpMIDITimedBigMessage( const MIDITimedBigMessage *msg);
    float next_event_time;
    MIDITimedBigMessage ev;
    int ev_track;
    std::clock_t start;
    double duration;

    const char *infile_name;

    MIDIFileReadStreamFile* rs;
    MIDIMultiTrack* tracks;
    MIDIFileReadMultiTrack* track_loader;
    MIDIFileRead* reader;
    MIDISequencer* seq;

};

#endif // MIDIMANAGER_H





