#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent, 
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

    //===============================================================================
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;

private:
    //==============================================================================
    // Your private member variables go here...
    juce::TextButton playButton{ "PLAY"};
    juce::TextButton stopButton{ "STOP" };
    juce::Slider volumeSlider{};

    juce::Random random;
    bool playing;

    double gain;
    float phase;
    double dphase;

    juce::AudioFormatManager formatManager;
    juce::AudioTransportSource transportSource;
    std::unique_ptr<AudioFormatReaderSource> readerSource;

    juce::TextButton loadButton;
    void loadURL(URL audioURL);


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
