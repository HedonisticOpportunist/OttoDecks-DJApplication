/*
  ==============================================================================

    MusicLibraryControlDeck.h
    Author:  anita.pal

  ==============================================================================
*/

#pragma once
#include "ControlDeck.h"
#include "DJAudioPlayer.h"
#include <JuceHeader.h>

class MusicLibraryControlDeck  : public juce::Component,
                                 public Button::Listener
{
public:
    MusicLibraryControlDeck
    (
        ControlDeck* _controlDeckOne, 
        ControlDeck* _controlDeckTwo
    );

    ~MusicLibraryControlDeck() override;

    void paint (juce::Graphics&) override;

    void resized() override;

    void buttonClicked(Button* button) override;

    void repaintButtons();


private:

    // Text Buttons 
    TextButton rewindButton{ "<< Rewind" };
    TextButton fastForwardButton{ "FastForward >>" };
    TextButton loopButton{ "Loop ()" };

    // ControlDeck One and Two
    ControlDeck* controlDeckOne;
    ControlDeck* controlDeckTwo;


    // background image 
    Image backgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicLibraryControlDeck)
};
