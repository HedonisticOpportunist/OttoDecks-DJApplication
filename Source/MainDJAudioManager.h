/*
  ==============================================================================

    MainDJAudioManager.h
    Author:  anita.pal

  ==============================================================================
*/

#pragma once
#include "ControlDeck.h"
#include "DJAudioPlayer.h"
#include <JuceHeader.h>
#include "MusicControlDeck.h"
#include "PlayListComponent.h"

class MainDJAudioManager : public juce::AudioAppComponent
                  
{
public:
    
    MainDJAudioManager();

    ~MainDJAudioManager() override;

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;

    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;

    void releaseResources() override;

    void paint (juce::Graphics& g) override;

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

    // Player List 
    DJAudioPlayer metadataCheckPlayer{ formatManager };
    PlaylistComponent playlistComponent{&deck1, &deck2, &metadataCheckPlayer};
    MusicControlDeck musicControlDeck{&playlistComponent};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainDJAudioManager)
};
