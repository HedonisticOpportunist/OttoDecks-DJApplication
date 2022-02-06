/*
  ==============================================================================

    AudioMetaData.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include "AudioMetaData.h"

AudioMetaData::AudioMetaData(DJAudioPlayer* _djAudioPlayer)
    :djAudioPlayer(_djAudioPlayer)
{

}

AudioMetaData::~AudioMetaData()
{

}

//R3B: Component parses and displays meta data such as filenameand song length
juce::String AudioMetaData::getAudioTrackLength(juce::URL& audioURL)
{
    djAudioPlayer->loadURL(audioURL);
    double seconds{ djAudioPlayer->determineFileLengthInSeconds() };
    juce::String minutes{ convertSecondsToMinutes(seconds) };
    return minutes;
}

juce::String AudioMetaData::convertSecondsToMinutes(double& seconds)
{
    int secondsRounded{ int(std::round(seconds))};

    juce::String minutesString{std::to_string(secondsRounded / 60)};
    juce::String secondsString{ std::to_string(secondsRounded % 60)};

    if (secondsString.length() < 2)
    {
        secondsString = secondsString.paddedLeft('0', 2);
    }

    return juce::String{minutesString + ":" + secondsString};
}