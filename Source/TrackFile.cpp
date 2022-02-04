/*
  ==============================================================================

    TrackFile.cpp
    Author:  anita.pal

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

juce::File TrackFile::getTrackFileProperties()
{
    return trackFile;
}

void TrackFile::setFileLength(std::string length)
{
    this->fileLength = length;
}

std::string TrackFile::getFileLength()
{
    return fileLength; 
}

juce::URL TrackFile::getFileURL()
{
    return fileURL;
}