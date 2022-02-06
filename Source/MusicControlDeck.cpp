/*
  ==============================================================================

    MusicControlDeck.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MusicControlDeck.h"

MusicControlDeck::MusicControlDeck(PlayListManager* _playList): playList(_playList)
{
    // background image 
    // @credit goes to https://unsplash.com/@gradienta
    backgroundImage = ImageCache::getFromMemory(BinaryData::background_img_png, BinaryData::background_img_pngSize);

    // make buttons visible 
    addAndMakeVisible(loadTrack);
    addAndMakeVisible(loadToDeckOne);

    addAndMakeVisible(loadToDeckTwo);
    addAndMakeVisible(removeTrack);

    // add listeners to the buttons 
    loadTrack.addListener(this);
    loadToDeckOne.addListener(this);
    loadToDeckTwo.addListener(this);
    removeTrack.addListener(this);

}

MusicControlDeck::~MusicControlDeck()
{
}

// R4C: GUI layout includes the music library component from R3
void MusicControlDeck::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::whitesmoke);
    graphics.drawImage(backgroundImage, getLocalBounds().toFloat());

    //A call to the buttons and sliders painting functions
    repaintButtons();
}

void MusicControlDeck::resized()
{
    double rowH = getHeight() / 4.0;

    // play, stop and load button positions
    loadTrack.setBounds(0, 0, getWidth() / 2.0, rowH * 1.0);
    loadToDeckOne.setBounds(0, rowH * 1.0, getWidth() / 2.0, rowH * 1.0);
    loadToDeckTwo.setBounds(0, rowH * 2.0, getWidth() / 2.0, rowH * 1.0);
    removeTrack.setBounds(0, rowH * 3.0, getWidth() / 2.0, rowH * 1.0);
}

void MusicControlDeck::repaintButtons()
{
    // set the colour for the load to deck one button if mouse over OR it has stopped playing 
    if (loadToDeckOne.isOver() || loadToDeckOne.isMouseOver())
    {
        loadToDeckOne.setColour(juce::TextButton::buttonColourId, juce::Colours::mistyrose);
    }

    // set the colour of the load to deck one button when mouse is not hovering over it 
    else
    {
        loadToDeckOne.setColour(juce::TextButton::buttonColourId, juce::Colours::olive);
    }

    // set the colour for the load to deck two button if mouse over OR it has stopped playing 
    if (loadToDeckTwo.isOver() || loadToDeckTwo.isMouseOver())
    {
        loadToDeckTwo.setColour(juce::TextButton::buttonColourId, juce::Colours::lightcoral);
    }

    // set the colour of the load to deck two button when mouse is not hovering over it 
    else
    {
        loadToDeckTwo.setColour(juce::TextButton::buttonColourId, juce::Colours::gainsboro);
    }

    // set the colour for the load button if mouse over OR it has stopped playing 
    if (loadTrack.isOver() || loadTrack.isMouseOver())
    {
        loadTrack.setColour(juce::TextButton::buttonColourId, juce::Colours::cornsilk);
    }

    // set the colour of the load button when mouse is not hovering over it 
    else
    {
        loadTrack.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
    }

    // set the colour for the remove button if mouse over OR it has stopped playing 
    if (removeTrack.isOver() || removeTrack.isMouseOver())
    {
        removeTrack.setColour(juce::TextButton::buttonColourId, juce::Colours::lemonchiffon);
    }

    // set the colour of the remove button when mouse is not hovering over it 
    else
    {
        removeTrack.setColour(juce::TextButton::buttonColourId, juce::Colours::navy);
    }
}

void MusicControlDeck::buttonClicked(Button* button)
{
    if (button == &loadTrack)
    {
        populateTrackListVector();
    }

    // add track to either of the decks
    if (button == &loadToDeckOne)
    {
        playList->addTrackToPlayerOne();
    }

    if (button == &loadToDeckTwo)
    {
        playList->addTrackToPlayerTwo();
    }

    if (button == &removeTrack)
    {
        removeAllContentsFromFile();
    }
}

// R3A: Component allows the user to add files to their library
juce::Array<juce::File> MusicControlDeck::loadInTracks()
{
    juce::Array<juce::File> trackFiles{};
    juce::String filters = "*.mp3";
    Array<File> file;

    juce::FileChooser chooser{ "Select files" };

    if (chooser.browseForMultipleFilesToOpen())
    {
        trackFiles = chooser.getResults();
    }

    return trackFiles;
}

bool MusicControlDeck::checkIfTrackAlreadyLoaded(TrackFile& trackFile)
{
    bool trackAlreadyLoaded = false;

    for (TrackFile& existingTrackFile : filesAlreadyLoaded)
    {
        if (existingTrackFile.getFileName() == trackFile.getFileName())
        {
            trackAlreadyLoaded = true;
        }
    }

    return trackAlreadyLoaded;
}

void MusicControlDeck::populateTrackListVector()
{
    std::ofstream fileList;

    // append the track list into the existing play list 
    fileList.open("tracks.txt", std::fstream::app);
   
    juce::Array<juce::File> files = loadInTracks();

    for (File& file : files)
    {
       TrackFile trackFile{file};

       if (!checkIfTrackAlreadyLoaded(trackFile))
       {
           filesAlreadyLoaded.push_back(trackFile);
           fileList << trackFile.getTrackFileProperties().getFullPathName() << "\n";
           playList->addTracksToFile(trackFile);
       }
    }

    fileList.close();
}

void MusicControlDeck::removeAllContentsFromFile()
{
    std::ofstream trackListToDelete;

    trackListToDelete.open("tracks.txt", std::ofstream::out | std::ofstream::trunc);
    trackListToDelete.close();

    playList->deleteTracks();
}