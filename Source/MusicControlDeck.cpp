/*
  ==============================================================================

    MusicControlDeck.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MusicControlDeck.h"

MusicControlDeck::MusicControlDeck
(
    ControlDeck* _controlDeckOne,
    ControlDeck* _controlDeckTwo)
    : controlDeckOne(_controlDeckOne), controlDeckTwo(_controlDeckTwo)
        
{
    // background image 
    // @credit https://unsplash.com/@gradienta
    backgroundImage = ImageCache::getFromMemory(BinaryData::background_img_png, BinaryData::background_img_pngSize);

    // make buttons visible 
    addAndMakeVisible(loadButton);
    addAndMakeVisible(loadToDeckOne);
    addAndMakeVisible(loadToDeckTwo);

    // add listeners to the buttons 
    loadButton.addListener(this);
    loadToDeckOne.addListener(this);
    loadToDeckTwo.addListener(this);

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
    double rowH = getHeight() / 3.0;

    // play, stop and load button positions
    loadButton.setBounds(0, 0, getWidth() / 2, rowH * 1.0);
    loadToDeckOne.setBounds(0, rowH * 1.0, getWidth() / 2, rowH * 1.0);
    loadToDeckTwo.setBounds(0, rowH * 2.0, getWidth() / 2, rowH * 1.0);
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
    if (loadButton.isOver() || loadButton.isMouseOver())
    {
        loadButton.setColour(juce::TextButton::buttonColourId, juce::Colours::cornsilk);
    }

    // set the colour of the load button when mouse is not hovering over it 
    else
    {
        loadButton.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
    }
}

//R3D: Component allows the user to load files from the library into a deck
void MusicControlDeck::addToDeck(ControlDeck* deck)
{
    //deck->loadDroppedTrack(audioURL);
}

void MusicControlDeck::buttonClicked(Button* button)
{
    if (button == &loadButton)
    {
        populateTrackListVector();
    }

    // add trakcs to one of the decks 
    if (button == &loadToDeckOne)
    {
        addToDeck(controlDeckOne);
    }

    if (button == &loadToDeckTwo)
    {
        addToDeck(controlDeckTwo);
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
        juce::Array<juce::File> trackFiles = chooser.getResults();
    }

    return trackFiles;
}

bool MusicControlDeck::checkIfTrackHasBeenLoaded(std::vector<TrackFile>& trackList)
{
    bool trackAlreadyLoaded = false;

    for (TrackFile& existingTrackFile : trackList)
    {
        if (existingTrackFile.getFileName() == existingTrackFile.getFileName())
        {
            trackAlreadyLoaded = true;
        }
    }

    return trackAlreadyLoaded;
}

void MusicControlDeck::populateTrackListVector()
{
    std::ofstream playList;
    playList.open("playlist.txt");
   
    juce::Array<juce::File> files = loadInTracks();

    for (juce::File& file : files)
    {
       TrackFile trackFile{ file };
       playList << trackFile.getFileName() << "\n";
        
    }

    playList.close();
}