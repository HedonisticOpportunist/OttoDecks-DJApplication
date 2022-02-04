/*
  ==============================================================================

    MusicControlDeck.h
    Author:  anita.pal

  ==============================================================================
*/

#pragma once
#include "ControlDeck.h"
#include <fstream>
#include <iostream>
#include "DJAudioPlayer.h"
#include <JuceHeader.h>
#include "PlayListManager.h"
#include "TrackFile.h"

class MusicControlDeck : public juce::Component,
                                public Button::Listener
{
public:
    MusicControlDeck(ControlDeck* _controlDeckOne, ControlDeck* _controlDeckTwo);

    ~MusicControlDeck() override;

    void paint(juce::Graphics&) override;

    void resized() override;

    void buttonClicked(Button* button) override;

    void repaintButtons();

    void addToDeck(ControlDeck* deck);

    void populateTrackListVector();

    juce::Array<juce::File> loadInTracks();

private:

    // Text Buttons 
    TextButton loadButton{ "Load" };
    TextButton loadToDeckOne{ "Load to Deck One" };
    TextButton loadToDeckTwo{ "Load to Deck Two" };

    // ControlDeck One and Two
    ControlDeck* controlDeckOne;
    ControlDeck* controlDeckTwo;

    // background image 
    Image backgroundImage;

    bool checkIfTrackHasBeenLoaded(std::vector<TrackFile>& trackList);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MusicControlDeck)
};