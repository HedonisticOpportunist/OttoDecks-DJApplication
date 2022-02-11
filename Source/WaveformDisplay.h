/*
  ==============================================================================

    WaveformDisplay.h
    Author:  anita.pal

    This component displays a waveform. 
  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class WaveformDisplay  : public juce::Component,
                         public ChangeListener
{
public:

    /** The WaveformDisplay constructor */
    WaveformDisplay(AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse);

    /** The WaveformDisplay destructor */
    ~WaveformDisplay() override;

    /** Paints the waveform */
    void paint (juce::Graphics&) override;

    /** Resizes the waveform */
    void resized() override;

    /** Loads the url */
    void loadURL(URL audioURL);

    /** Changes the listener's callback */
    void changeListenerCallback(ChangeBroadcaster* source) override;

    /** Sets the relative position of the play's head */
    void setPositionRelative(double pos);

private:

    // private members 
    AudioThumbnail audioThumbnail;
    bool fileLoaded;
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
