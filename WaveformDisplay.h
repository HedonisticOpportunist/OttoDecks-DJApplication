/*
  ==============================================================================

    WaveformDisplay.h
    Created: 22 Jan 2022 12:24:54pm
    Author:  anita.pal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public ChangeListener
{
public:
    WaveformDisplay(AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay();

    void paint (juce::Graphics&) override;
    void resized() override;
    void loadURL(URL audioURL);
    void changeListenerCallback(ChangeBroadcaster* source) override;
    /** set the relative position of the play head*/
    void setPositionRelative(double pos);

private:

    AudioThumbnail audioThumbnail;
    bool fileLoaded;
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
