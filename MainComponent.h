#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AudioAppComponent, 
                      public Button::Listener,
                      public Slider::Listener
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

    void buttonClicked(Button *) override;
    void sliderValueChanged(Slider*) override;

private:
    //==============================================================================
    // Your private member variables go here...
    
    //required enums
    TextButton playButton{ "PLAY", "Click Play!" };
    TextButton stopButton{ "STOP", "Click Stop!" };
    Slider volumeSlider{};



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
