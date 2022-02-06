/*
  ==============================================================================

    AudioMetaData.h
    Author: @ anita.pal

    This class deals with gathering audio metadata information related to file 
    length which is retrieved from the DJAudioPlayer class.

  ==============================================================================
*/

#pragma once
#include <algorithm>
#include "DJAudioPlayer.h"
#include "JuceHeader.h"

class AudioMetaData 
{

public:
    /** AudioMetaData constructor */
    AudioMetaData(DJAudioPlayer* _djAudioPlayer);

    /** AudioMetaData destructor */
    ~AudioMetaData();

    /** Returns the audio track length */
    juce::String getAudioTrackLength(juce::URL& audioURL);

private:

    /** A pointer to the DJAudioPlayer class */
    DJAudioPlayer* djAudioPlayer;

    /** Returns a formatted audio string */
    juce::String getFormattedAudioString(double& seconds);
};