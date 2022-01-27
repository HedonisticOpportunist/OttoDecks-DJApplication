/*
  ==============================================================================

    WaveformDisplay.h
    Author:  anita.pal

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class WaveformDisplay  : public juce::Component,
                         public ChangeListener
{
public:

    /** The wave form constructor  */
    WaveformDisplay(AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse);

    /** The waveform destructor */
    ~WaveformDisplay();

    /** Paint the wave form */
    void paint (juce::Graphics&) override;

    /** Resize the waveform */
    void resized() override;

    /** Load the url */
    void loadURL(URL audioURL);

    /** Change the listener callback */
    void changeListenerCallback(ChangeBroadcaster* source) override;

    /** set the relative position of the play head */
    void setPositionRelative(double pos);

private:

    // private members 
    AudioThumbnail audioThumbnail;
    bool fileLoaded;
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
