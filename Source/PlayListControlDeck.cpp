/*
  ==============================================================================

    PlayListControlDeck.cpp
    Author: @anita.pal

    The implementation of the PlayListControlDeck component. 
  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayListControlDeck.h"

PlayListControlDeck::PlayListControlDeck(PlayListManager* _playList): playList(_playList)
{
    // background image 
    // @credit goes to <a href="https://www.vecteezy.com/free-vector/cat">Cat Vectors by Vecteezy</a>
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

PlayListControlDeck::~PlayListControlDeck()
{
}

void PlayListControlDeck::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::whitesmoke);
    graphics.drawImage(backgroundImage, getLocalBounds().toFloat());

    // A call to the buttons and sliders painting functions
    repaintButtons();
}

void PlayListControlDeck::resized()
{
    double rowH = getHeight() / 4.0;

    // The play, stop and load button positions
    loadTrack.setBounds(0, 0, getWidth() / 2.0, rowH * 1.0);
    loadToDeckOne.setBounds(0, rowH * 1.0, getWidth() / 2.0, rowH * 1.0);
    loadToDeckTwo.setBounds(0, rowH * 2.0, getWidth() / 2.0, rowH * 1.0);
    removeTrack.setBounds(0, rowH * 3.0, getWidth() / 2.0, rowH * 1.0);
}

void PlayListControlDeck::repaintButtons()
{
    // set the colour for the load to deck one button if mouse over OR it has stopped playing 
    if (loadToDeckOne.isOver() || loadToDeckOne.isMouseOver())
    {
        loadToDeckOne.setColour(juce::TextButton::buttonColourId, juce::Colours::mistyrose);
    }

    // set the colour of the load to deck one button when the mouse is not hovering over it 
    else
    {
        loadToDeckOne.setColour(juce::TextButton::buttonColourId, juce::Colours::olive);
    }

    // set the colour for the load to deck two button if mouse over OR it has stopped playing 
    if (loadToDeckTwo.isOver() || loadToDeckTwo.isMouseOver())
    {
        loadToDeckTwo.setColour(juce::TextButton::buttonColourId, juce::Colours::lightcoral);
    }

    // set the colour of the load to deck two button when the mouse is not hovering over it 
    else
    {
        loadToDeckTwo.setColour(juce::TextButton::buttonColourId, juce::Colours::gainsboro);
    }

    // set the colour for the load button if mouse over OR it has stopped playing 
    if (loadTrack.isOver() || loadTrack.isMouseOver())
    {
        loadTrack.setColour(juce::TextButton::buttonColourId, juce::Colours::cornsilk);
    }

    // set the colour of the load button when the mouse is not hovering over it 
    else
    {
        loadTrack.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
    }

    // set the colour for the remove button if mouse over OR it has stopped playing 
    if (removeTrack.isOver() || removeTrack.isMouseOver())
    {
        removeTrack.setColour(juce::TextButton::buttonColourId, juce::Colours::lemonchiffon);
    }

    // set the colour of the remove button when the mouse is not hovering over it 
    else
    {
        removeTrack.setColour(juce::TextButton::buttonColourId, juce::Colours::navy);
    }
}

void PlayListControlDeck::buttonClicked(Button* button)
{
    if (button == &loadTrack)
    {
        populateTracksFile(); // add a track to the tracks.txt file 
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
        removeAllContentsFromFile(); // remove all contents from the tracks.txt file 
    }
}

juce::Array<juce::File> PlayListControlDeck::loadInTracks()
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

bool PlayListControlDeck::checkIfTrackAlreadyLoaded(TrackFile& trackFile)
{
    bool trackAlreadyLoaded = false;

    for (TrackFile& existingTrackFile : filesAlreadyLoaded)
    {
        if (existingTrackFile.getFileName() == trackFile.getFileName()) // if the file names match 
        {
            trackAlreadyLoaded = true;
        }
    }

    return trackAlreadyLoaded;
}

void PlayListControlDeck::populateTracksFile()
{
    std::ofstream fileList;

    // append the track list into the existing playlist 
    fileList.open("tracks.txt", std::fstream::app);
   
    juce::Array<juce::File> files = loadInTracks();

    for (File& file : files)
    {
       TrackFile trackFile{file};

       if (!checkIfTrackAlreadyLoaded(trackFile))
       {
           filesAlreadyLoaded.push_back(trackFile);
           fileList << trackFile.getTrackFileProperties().getFullPathName() << "\n"; // display full file name of track 
           playList->addTrackToTracksVector(trackFile);
       }
    }

    fileList.close();
}

void PlayListControlDeck::removeAllContentsFromFile()
{
    std::ofstream trackListToDelete;

    // Remove all content from the tracks.txt file 
    trackListToDelete.open("tracks.txt", std::ofstream::out | std::ofstream::trunc);
    trackListToDelete.close();

    playList->deleteTracksFromTable();
}
