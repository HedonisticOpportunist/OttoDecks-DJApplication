/*
  ==============================================================================

    PlayListControlDeck.h
    Author:  anita.pal

    This component deals with the tracks.txt file and the event handling of 
    the PlayListManager component. 
  ==============================================================================
*/

#pragma once
#include <fstream>
#include <iostream>
#include "DJAudioPlayer.h"
#include <JuceHeader.h>
#include "PlayListManager.h"
#include "TrackFile.h"

class PlayListControlDeck : public juce::Component,
                                public Button::Listener
{
public:

    /** The MusicControlDeck constructor */
    PlayListControlDeck(PlayListManager* _playlist);

    /** The MusicControlDeck destructor */
    ~PlayListControlDeck() override;

    /** Paints onto the screen */
    void paint(juce::Graphics&) override;

    /** Resizes the screen */
    void resized() override;

    /** Deals with button clicks */
    void buttonClicked(Button* button) override;

    /** Populates the tracks txt file */
    void populateTracksFile();

    /** Removes all contents from the txt file */
    void removeAllContentsFromFile();

private:

    // Text Buttons 
    TextButton loadTrack{"Add Track to List"};
    TextButton loadToDeckOne{"Play Track in Deck One" };
    TextButton loadToDeckTwo{"Play Track in Deck Two" };
    TextButton removeTrack{"Remove All Tracks From List" };

    // PlayList Manager 
    PlayListManager* playList;

    // A list for tracking purposes
    std::vector<TrackFile> filesAlreadyLoaded;
    
    // Background image 
    Image backgroundImage;

    /** PRIVATE METHODS */
    
    /** Repaints buttons depending on specific properties */
    void repaintButtons();

    /** Checks if a track has already been loaded */
    bool checkIfTrackAlreadyLoaded(TrackFile& trackFile);

    /** Loads a track */
    juce::Array<juce::File> loadInTracks();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayListControlDeck)
};