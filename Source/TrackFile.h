/*
  ==============================================================================

    TrackFile.h
    Author:  anita.pal

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class TrackFile 
{

public:

    TrackFile(juce::File _file);

    ~TrackFile();

    juce::File getTrackFileProperties();

    juce::String getFileName(); 

    void setFileLength(juce::String);

    juce::String getFileLength();

    juce::URL getFileURL();

private:

    juce::File trackFile; 
    juce::URL fileURL;
    juce::String trackTitle;
    juce::String fileLength;
};
