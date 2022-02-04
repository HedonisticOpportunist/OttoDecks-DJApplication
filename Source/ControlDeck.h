/*
  ==============================================================================

    ControlDeck.h
    Author:  anita.pal

  ==============================================================================
*/

#pragma once

#include "DJAudioPlayer.h"
#include <JuceHeader.h>
#include "WaveformDisplay.h"

class ControlDeck : public juce::Component,
    public Button::Listener,
    public Slider::Listener,
    public Timer
{

public:
    /** The ControlDeck constructor */
    ControlDeck
    (
        DJAudioPlayer* _djAudioPlayer, 
        AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse
    );

    /** The ControlDeck destructor */
    ~ControlDeck() override;

    /** Paints the screen */
    void paint(juce::Graphics&) override;

    /** Resizes the screen */
    void resized() override;

    /** Deals with button clicks */
    void buttonClicked(Button* button) override;

    /** Deals with slider value changes */
    void sliderValueChanged(Slider* slider) override;

    /** Allows timer callback */
    void timerCallback() override;

    /** Repaint the buttons if they are not in use */
    void repaintButtons();

    /** Repaint the sliders if they are not in use */
    void repaintSliders();

    /** Deal with the differing states of the play button status */
    void displayPlayButtonText(bool paused);

    /** Load a file that has been dragged and dropped */
    void loadDroppedTrack(juce::URL url);

private:

    // buttons 
    TextButton playButton{ "Play |>" };
    TextButton stopButton{ "Stop / Pause ||| " };
    TextButton loadButton{ "Load" };

    TextButton rewindButton{ "<< Rewind" };
    TextButton fastForwardButton{ "FastForward >>" };
    TextButton loopButton{ "Loop ()" };

    // sliders 
    Slider volumeSlider;
    Slider positionSlider;
    Slider speedSlider;

    // wave form 
    WaveformDisplay waveformDisplay;

    // status of pause button 
    bool paused = false;

    // audio-related variables
    juce::FileChooser chooser{ "Browse audio file" };
    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControlDeck)
};