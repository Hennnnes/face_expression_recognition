#include "midimanager.h"


// Constructor
MidiManager::MidiManager():
    next_event_time(0.),
    start(std::clock()),
    duration(0.)
{

}


// Destructor
MidiManager::~MidiManager()
{

}

void MidiManager::initialize()
{
//    this->inst = inst;
//    this->infile_name = infile_name;

//    MIDIFileReadStreamFile rs_( infile_name );
//    rs = &rs_;
//    MIDIMultiTrack tracks_;
//    tracks = &tracks_;
//    MIDIFileReadMultiTrack track_loader_( &tracks_ );
//    track_loader = &track_loader_;
//    MIDIFileRead reader_( &rs_, &track_loader_ );
//    reader = &reader_;

//    tracks_.ClearAndResize( reader_.ReadNumTracks() );

//    MIDISequencer seq_( &tracks_ );
//    seq = &seq_;

//    if ( !reader_.Parse() )
//    {
//        return;
//    }

}

// set the Mixer
void MidiManager::setMixer(Mixer *mixer){
    this->mixer = mixer;
}

//set emotion to select suitable midi file
void MidiManager::setEmotion(int emotion){
    const char *infile_name;

    switch (emotion){
    //NEUTRAL
    case 0:
        infile_name = "C:\\Users\\Jan\\Desktop\\Medientechnik\\Semester 5\\AV-Programmierung\\test6.mid"; /***MidiFile für NEUTRAL einfügen*/
        break;
    //HAPPY
    case 1:
        infile_name = "a.mid"; /***MidiFile für HAPPY einfügen*/
        break;
    //SAD
    case 2:
        infile_name = "vrm.mid"; /***MidiFile für SAD einfügen*/
        break;
    //ANGRY
    case 3:
        /***MidiFile für ANGRY einfügen*/
        break;
    //SURPRISED
    case 4:
        /***MidiFile für SURPRISED einfügen*/
        break;
    }
    cerr << infile_name << endl;

    rs = new MIDIFileReadStreamFile( infile_name );
    //MIDIFileReadStreamFile rs( infile_name );
    tracks = new MIDIMultiTrack;
    //MIDIMultiTrack tracks;
    track_loader = new MIDIFileReadMultiTrack( tracks );
    //MIDIFileReadMultiTrack track_loader( &tracks );
    reader = new MIDIFileRead( rs, track_loader );
    //MIDIFileRead reader( &rs, &track_loader );

    // set amount of tracks equal to midifile
    tracks->ClearAndResize( reader->ReadNumTracks() );

    seq = new MIDISequencer(tracks);
    //MIDISequencer seq ( &tracks );

    // load the midifile into the multitrack object
    if ( !reader->Parse() )
    {
        cerr << "\nError parse file " << infile_name << endl;

    }
    else{
        this->seq = seq;
        update();
    }
}

void MidiManager::update(){
    seq->GoToTimeMs (duration);
    duration = (std::clock() - start);

    if ( !seq->GetNextEventTimeMs ( &next_event_time ) )
    {
        return;
    }

    if(next_event_time <= duration){
        seq->GetNextEvent(&ev_track, &ev);
        int channel = ev.GetChannel() + 1;
        int note = ev.GetNote();
        float velocity = ev.GetVelocity();
        double frequency = pow(2,(note-69.0)/12.0)*440;
        DumpMIDITimedBigMessage(&ev);
        if(ev.IsNoteOn()){
            mixer -> on(frequency, velocity);
        }
        if(ev.IsNoteOff()){
            mixer -> off(frequency);
        }
    }
}

void MidiManager::DumpMIDITimedBigMessage( const MIDITimedBigMessage *msg)
{
    if (msg){
        char msgbuf[1024];

        if (!msg->IsBeatMarker()){

            int channel = msg -> GetChannel() + 1;
            int note = msg -> GetNote();
            float velocity = msg -> GetVelocity();
            double frequency = pow(2,(note-69.0)/12.0)*440;

            if (msg -> IsNoteOn()){
                mixer -> on(frequency, velocity);
            }
            else if (msg -> IsNoteOff() || velocity == 0){
                mixer -> off(frequency);
            }
        }
    }
}


