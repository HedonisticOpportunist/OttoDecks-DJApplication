/*
  ==============================================================================

    DeckGui.h
    Created: 21 Jan 2022 8:46:01pm
    Author:  anita.pal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class DeckGui  : public juce::Component,
                 public Button::Listener,
                 public Slider::Listener,
                 public FileDragAndDropTarget
{
public:
    DeckGui(DJAudioPlayer* _djAudioPlayer);
    ~DeckGui() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;
    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

private:
    TextButton playButton
    {
        "PLAY"
    };
        
    TextButton stopButton
    { 
        
        "STOP" 
    };
    TextButton loadButton
    {
        "LOAD"
    };
    Slider volumeSlider;
    Slider positionSlider;
    Slider speedSlider;

    juce::FileChooser chooser{ "Browse audio file" };
    DJAudioPlayer* djAudioPlayer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGui)
};
