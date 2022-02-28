/*
  ==============================================================================

    ControlDeck.h
    Author:  @anita.pal

    This component deals with button clicks and the way audio is controlled 
    via the DJAudioPlayer class. 
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

    /** Paints on the screen */
    void paint(juce::Graphics&) override;

    /** Resizes the screen */
    void resized() override;

    /** Deals with button clicks */
    void buttonClicked(Button* button) override;

    /** Deals with slider value changes */
    void sliderValueChanged(Slider* slider) override;

    /** Allows timer callback */
    void timerCallback() override;

    /** Loads a file that has been dragged and dropped */
    void loadDroppedTrack(juce::URL& url);

private:

    // Image Buttons 
    ImageButton rewindButton;
    ImageButton fastForwardButton;
    ImageButton loopButton;

    // Text Button 
    TextButton playButton{ "Play |>" };
    TextButton stopButton{ "Stop / Pause ||| " };
    TextButton loadButton{ "Load" };

    // Text Labels
    Label volumeLabel;
    Label positionLabel;
    Label speedLabel; 

    // Sliders 
    Slider volumeSlider;
    Slider positionSlider;
    Slider speedSlider;

    // Waveform
    WaveformDisplay waveformDisplay;

    // Default status of the pause button 
    bool paused = false;

    // Audio-related variables
    juce::FileChooser chooser{ "Browse audio file" };
    DJAudioPlayer* player;
    
    /** PRIVATE METHODS */

    /** Repaints the buttons */
    void repaintButtons(); 

    /** Redraws the colours of the sliders differently depending on specific conditions */
    void repaintSliders();

    /** Display the play button text depending on differing statues */
    void displayPlayButtonText(bool paused);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControlDeck)
};