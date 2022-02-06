/*
  ==============================================================================

    AudioMetaData.h
    Author:  anita.pal

  ==============================================================================
*/

#pragma once
#include <algorithm>
#include "DJAudioPlayer.h"
#include "JuceHeader.h"

class AudioMetaData {

public:
    AudioMetaData(DJAudioPlayer* _djAudioPlayer);

    ~AudioMetaData();

    juce::String getAudioTrackLength(juce::URL& audioURL);

    juce::String convertSecondsToMinutes(double& seconds);

private:

    DJAudioPlayer* djAudioPlayer;
};