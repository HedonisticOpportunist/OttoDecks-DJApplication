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
}

MusicLibraryManager::~MusicLibraryManager()
{
    // R3E: The music library persists so that it is restored 
    // when the user exits then restarts the application
    saveTracksToPlaylist();
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
            g.drawText(trackList[rowNumber].getFileNameWithoutExtension(),
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
    int id = std::stoi(button->getComponentID().toStdString());
    tableComponent.updateContent();
}

void MusicLibraryManager::saveTracksToPlaylist()
{
    // create .csv to save library
    //std::ofstream fileToSave("playlist.csv");

    // save library to file
    for (auto &track : trackList)
    {
        //fileToSave << track.getFullPathName() << "," << "\n";
    }
}

/* void PlaylistComponent::loadLibrary()
{
    // create input stream from saved library
    std::ifstream loadedLibrary("my-library.csv");
    std::string filePath;
    std::string length;

    // Read data, line by line
    if (myLibrary.is_open())
    {
        while (getline(myLibrary, filePath, ',')) {
            juce::File file{ filePath };
            Track newTrack{ file };

            getline(myLibrary, length);
            newTrack.length = length;
            tracks.push_back(newTrack);
        }
    }
    myLibrary.close();
} */