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

    juce::String getFileName(); 

    void setFileLength(juce::String length);

    juce::String getFileLength();

    juce::URL getFileURL();

private:
    juce::File trackFile; 
    juce::URL fileURL;
    juce::String trackTitle;
    juce::String fileLength = "2";
};
