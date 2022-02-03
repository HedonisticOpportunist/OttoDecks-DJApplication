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
#include "MusicLibraryManager.h"

class MusicLibraryControlDeck  : public juce::Component,
                                 public Button::Listener
{
public:
    MusicLibraryControlDeck(ControlDeck* _controlDeckOne, ControlDeck* _controlDeckTwo);

    ~MusicLibraryControlDeck() override;

    void paint (juce::Graphics&) override;

    void resized() override;

    void buttonClicked(Button* button) override;

    void repaintButtons();

    void loadTracks();

    void addToDeck(ControlDeck* deck);

private:

    // Text Buttons 
    TextButton loadButton{ "Load" };
    TextButton loadToDeckOne{ "Load to Deck One" };
    TextButton loadToDeckTwo{ "Load to Deck Two" };

    // Audio components 
    juce::FileChooser chooser{ "Browse audio file" };
    URL audioURL;

    // ControlDeck One and Two
    ControlDeck* controlDeckOne;
    ControlDeck* controlDeckTwo;

    // background image 
    Image backgroundImage;

    // Music Library Manager object
    MusicLibraryManager musicLibraryManager; 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicLibraryControlDeck)
};
