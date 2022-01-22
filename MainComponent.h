#pragma once

#include "DeckGui.h"
#include "DJAudioPlayer.h"
#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
                  
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{ 100 };
    DJAudioPlayer player1{formatManager};
    DeckGui deck1{ &player1, formatManager, thumbCache};

    DJAudioPlayer player2{formatManager};
    DeckGui deck2{&player2, formatManager, thumbCache};

    MixerAudioSource mixerSource;
    PlaylistComponent playlistComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
