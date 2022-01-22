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
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGui  : public juce::Component,
                 public Button::Listener,
                 public Slider::Listener,
                 public FileDragAndDropTarget,
                 public Timer 
{
public:
    DeckGui(DJAudioPlayer* _djAudioPlayer, AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse);
    ~DeckGui() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;
    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;
    void timerCallback() override;

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
    WaveformDisplay waveformDisplay; 

    juce::FileChooser chooser{ "Browse audio file" };

    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGui)
};
