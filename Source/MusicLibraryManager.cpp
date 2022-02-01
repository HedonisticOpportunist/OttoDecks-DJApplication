/*
  ==============================================================================

    MusicLibraryManager.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MusicLibraryManager.h"

MusicLibraryManager::MusicLibraryManager()
{
 
    // column and tracks 
    tableComponent.getHeader().addColumn("Track title", 1, 150);
    tableComponent.getHeader().addColumn("Duration", 2, 100);
    tableComponent.getHeader().addColumn("First Deck", 3, 100);
    tableComponent.getHeader().addColumn("Second Deck", 4, 100);
    tableComponent.setModel(this);  

    // make table component visible 
    addAndMakeVisible(tableComponent); 
   
    trackList.push_back("Track 1");
    trackList.push_back("Track 2");
    trackList.push_back("Track 3");
    trackList.push_back("Track 4");
}

MusicLibraryManager::~MusicLibraryManager()
{
}

// R4C: GUI layout includes the music library component from R3
void MusicLibraryManager::paint (juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::beige);
    graphics.drawRect (getLocalBounds(), 1);   
    graphics.setColour (juce::Colours::white);
}

void MusicLibraryManager::resized()
{
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int MusicLibraryManager::getNumRows()
{
    return trackList.size();
}

void MusicLibraryManager::paintRowBackground(Graphics& g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::lavenderblush);
    }
    else {
        g.fillAll(Colours::aquamarine);
    }
}

void MusicLibraryManager::paintCell(Graphics& g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected)
{
    if (rowNumber < getNumRows())
    {
        if (columnId == 1)
        {
            g.drawText(trackList[rowNumber],
                2,
                0,
                width - 4,
                height,
                juce::Justification::centredLeft,
                true
            );
        }
    }
}

// @ credit goes to: 
// https://stackoverflow.com/questions/69111741/
// how-do-i-add-an-playable-audio-file-to-a-tablelistbox-playlist-juce-c
Component* MusicLibraryManager::refreshComponentForCell(
    int rowNumber,
    int columnId,
    bool isRowSelected,
    Component* existingComponentToUpdate)
{
    if (columnId == 0) 
    {
        jassert(existingComponentToUpdate == nullptr);
        return nullptr;
    }

    if (columnId == 1)
    {
        TextButton* btn = static_cast<TextButton*> (existingComponentToUpdate);

        if (btn == 0)
        {
            btn = new TextButton{ "Play" };
        }

        String id{ std::to_string(rowNumber) };
        btn->setComponentID(id);
        btn->addListener(this);
        existingComponentToUpdate = btn;
    }

    return existingComponentToUpdate;
}

// @ credit goes to: 
// https://stackoverflow.com/questions/69111741/
// how-do-i-add-an-playable-audio-file-to-a-tablelistbox-playlist-juce-c
void MusicLibraryManager::buttonClicked(Button* button)
{
    // player->loadURL(file[std::stoi(button->getComponentID().toStdString())]);
    // player->start();
}

// @ credit goes to: 
// https://stackoverflow.com/questions/69111741/
// how-do-i-add-an-playable-audio-file-to-a-tablelistbox-playlist-juce-c
void MusicLibraryManager::updateTracks(Array<File> trackFile)
{
    for (unsigned int i = 0; i < trackFile.size(); ++i)
    {
        // ge the file name 
        trackList.push_back(trackFile[i].getFileName());

    }

    tableComponent.updateContent();
}