/*
  ==============================================================================

    TrackFile.h
    Author:  @anita.pal

    This class is a representation of a track file and its respective
    properties. 
  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class TrackFile 
{

public:

    /** The TrackFile constructor */
    TrackFile(juce::File _file);

    /** The TrackFile destructor */
    ~TrackFile();

    /** Returns track file properties */
    juce::File getTrackFileProperties();

    /** Returns the file name  */
    juce::String getFileName(); 

    /**- Sets the file length */
    void setFileLength(juce::String& length);

    /** Returns the file length */
    juce::String getFileLength();

    /** Gets the file url */
    juce::URL getFileURL();

private:

    // Class specific variables 
    juce::File trackFile; 
    juce::URL fileURL;
    juce::String trackTitle;
    juce::String fileLength;
};
