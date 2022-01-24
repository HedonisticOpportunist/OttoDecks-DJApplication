#pragma once
#include "ControlDeck.h"
#include "DJAudioPlayer.h"
#include <JuceHeader.h>
#include "PlaylistComponent.h"
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
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{ 100 };
    DJAudioPlayer player1{formatManager};
    ControlDeck deck1{ &player1, formatManager, thumbCache};

    DJAudioPlayer player2{formatManager};
    ControlDeck deck2{&player2, formatManager, thumbCache};

    MixerAudioSource mixerSource;
    PlaylistComponent playlistComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
