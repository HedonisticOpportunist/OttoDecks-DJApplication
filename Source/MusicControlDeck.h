/*
  ==============================================================================

    MusicControlDeck.h
    Author:  anita.pal

  ==============================================================================
*/

#pragma once
#include <fstream>
#include <iostream>
#include "DJAudioPlayer.h"
#include <JuceHeader.h>
#include "PlayListComponent.h"
#include "TrackFile.h"

class MusicControlDeck : public juce::Component,
                                public Button::Listener
{
public:
    MusicControlDeck(PlayListComponent* _playlist);

    ~MusicControlDeck() override;

    void paint(juce::Graphics&) override;

    void resized() override;

    void buttonClicked(Button* button) override;

    void repaintButtons();

    void populateTrackListVector();

    bool checkIfTrackAlreadyLoaded(TrackFile& trackFile);

    juce::Array<juce::File> loadInTracks();

    void removeAllContentsFromFile();

private:

    // Text Buttons 
    TextButton loadTrack{"Add Track to List"};
    TextButton loadToDeckOne{"Play Track in Deck One" };
    TextButton loadToDeckTwo{"Play Track in Deck Two" };
    TextButton removeTrack{"Remove All Tracks From List" };

    // PlayListComponent 
    PlayListComponent* playList;

    // Existing Track List for trackiing purposes
    std::vector<TrackFile> filesAlreadyLoaded;

    // background image 
    Image backgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MusicControlDeck)
};