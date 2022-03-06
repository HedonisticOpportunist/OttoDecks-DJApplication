/*
  ==============================================================================

    AudioMetaData.cpp
    Author: @anita.pal

    The implementation of the AudioMetaData class. 
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
    djAudioPlayer->loadURL(audioURL); // pointer to the DJAudioPlayer calls for the url to get the necessary data aka the file length 

    // Get the file length from a pointer to the DJAudioPlayer class 
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
    int secondsRounded = int(std::round(seconds)); // round the seconds 

    // convert the time above into strings representing the hours, minutes and seconds 
    juce::String hoursString = std::to_string(secondsRounded / 3600);
    juce::String minutesString = std::to_string((secondsRounded / 60) % 60);
    juce::String secondsString{ std::to_string(secondsRounded % 60)};

    if (secondsString.length() < 2)
    {
        secondsString = secondsString.paddedLeft('0', 2); // if there are no seconds, just add the appropriate amount of zeros in their place 
    }
    
    // HOURS:MINUTES:SECONDS
    juce::String formattedAudioString = juce::String{hoursString + ":" + minutesString + ":" + secondsString};

    return formattedAudioString;
}