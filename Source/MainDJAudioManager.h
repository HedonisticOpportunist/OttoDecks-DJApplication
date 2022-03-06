/*
  ==============================================================================

    MainDJAudioManager.h
    Author: @anita.pal

    This component serves as a gateway for all the other components. 
  ==============================================================================
*/

#pragma once
#include "AudioMetaData.h"
#include "ControlDeck.h"
#include "DJAudioPlayer.h"
#include <JuceHeader.h>
#include "PlayListControlDeck.h"
#include "PlayListManager.h"
#include "SearchField.h"

class MainDJAudioManager : public juce::AudioAppComponent
                  
{
public:
    
    /** The MainDJAudioManager constructor */
    MainDJAudioManager();

    /** The MainDJAudioManager destructor */
    ~MainDJAudioManager() override;

    /** Prepares to play audio */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;

    /** Gets the next audio block */
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;

    /** Releases resources */
    void releaseResources() override;

    /** Paints onto the screen */
    void paint (juce::Graphics& g) override;

    /** Resizes the screen */
    void resized() override;

private:
  
    // background image 
    Image backgroundImage;

    // audio-related object instantiations 
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100};
    MixerAudioSource mixerSource;

    // Deck 1
    DJAudioPlayer deckOnePlayer{formatManager};
    ControlDeck deck1{ &deckOnePlayer, formatManager, thumbCache};

    // Deck 2
    DJAudioPlayer deckTwoPlayer{formatManager};
    ControlDeck deck2{&deckTwoPlayer, formatManager, thumbCache};

    // Audio Metadata
    DJAudioPlayer djAudioPlayer{formatManager};
    AudioMetaData audioMetaData{ &djAudioPlayer};

    // Player List 
    PlayListManager playListComponent{&audioMetaData, &deck1, &deck2};
    PlayListControlDeck musicControlDeck{&playListComponent};

    // Search Field 
    SearchField searchField{&playListComponent};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainDJAudioManager)
};
