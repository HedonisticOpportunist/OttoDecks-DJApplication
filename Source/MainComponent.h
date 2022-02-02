/*
  ==============================================================================

    MainComponent.h
    Author:  anita.pal

  ==============================================================================
*/

#pragma once
#include "ControlDeck.h"
#include "DJAudioPlayer.h"
#include <JuceHeader.h>
#include "MusicLibraryControlDeck.h"
#include "MusicLibraryManager.h"

class MainComponent  : public juce::AudioAppComponent
                  
{
public:
    
    MainComponent();

    ~MainComponent() override;

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
    DJAudioPlayer musicManagerPlayer{formatManager};
    //MusicLibraryManager musicLibraryManager;
    MusicLibraryControlDeck musicControlDeck{&musicManagerPlayer, formatManager};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
