/*
  ==============================================================================

    TrackFile.cpp
    Author:  @anita.pal

    The implementation of the TrackFile class. 
  ==============================================================================
*/

#include "TrackFile.h"
#include <filesystem>

TrackFile::TrackFile(juce::File _file)
{
    this->trackFile = _file; 
    this->trackTitle = _file.getFileNameWithoutExtension();
    this->fileURL = URL(juce::URL{ _file });
}

TrackFile::~TrackFile()
{

}

juce::String TrackFile::getFileName()
{
    return trackTitle;
}

// get specific file properties like the full path name
juce::File TrackFile::getTrackFileProperties()
{
    return trackFile;
}

void TrackFile::setFileLength(juce::String &length)
{
    this->fileLength = length;
}

juce::String TrackFile::getFileLength()
{
    return fileLength; 
}

juce::URL TrackFile::getFileURL()
{
    return fileURL;
}