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

juce::String AudioMetaData::getAudioTrackLength(juce::URL& audioURL)
{
    djAudioPlayer->loadURL(audioURL);

    // Get the file length from the DJAudioPlayer class 
    double seconds = djAudioPlayer->getFileLengthSeconds();

    // Return the string in an appropriate format
    juce::String audioLength = getFormattedAudioString(seconds);

    return audioLength;
}

/** 
@ credit goes to : 
https://www.csestack.org/online-tool-to-convert-seconds-to-hours-minutes-hhmmss/
**/
juce::String AudioMetaData::getFormattedAudioString(double& seconds)
{
    int secondsRounded = int(std::round(seconds));

    juce::String hoursString = std::to_string(secondsRounded / 3600);
    juce::String minutesString = std::to_string((secondsRounded / 60) % 60);
    juce::String secondsString{ std::to_string(secondsRounded % 60)};

    if (secondsString.length() < 2)
    {
        secondsString = secondsString.paddedLeft('0', 2);
    }
    
    // HOURS:MINUTES:SECONDS
    juce::String formattedAudioString = juce::String{hoursString + ":" + minutesString + ":" + secondsString};

    return formattedAudioString;
}