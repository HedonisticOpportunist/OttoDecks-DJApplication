/*
  ==============================================================================

    MusicLibraryControlDeck.h
    Author:  anita.pal

  ==============================================================================
*/

#pragma once
#include "DJAudioPlayer.h"
#include <JuceHeader.h>
#include "MusicLibraryManager.h"

class MusicLibraryControlDeck  : public juce::Component,
                                 public Button::Listener
{
public:
    MusicLibraryControlDeck(DJAudioPlayer* _dJPlayer, AudioFormatManager& formatManagerToUse);
    ~MusicLibraryControlDeck() override;

    void paint (juce::Graphics&) override;

    void resized() override;

    void buttonClicked(Button* button);

    void repaintButtons();

    void loadTracks();

    void addToDeck();

private:

    // Text Buttons 
    TextButton loadButton{ "Load" };
    TextButton loadToDeckOne{ "Load to Deck One" };
    TextButton loadToDeckTwo{ "Load to Deck Two" };

    // Audio components 
    juce::FileChooser chooser{ "Browse audio file" };
    DJAudioPlayer* player;

    // background image 
    Image backgroundImage;

    // Music Library Manager object
    //MusicLibraryManager musicLibraryManager; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicLibraryControlDeck)
};
