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
 
    // Set the columns 
    tableComponent.getHeader().addColumn("Track Title", 1, 150);
    tableComponent.getHeader().addColumn("Duration", 2, 100);
    tableComponent.getHeader().addColumn("First Deck", 3, 100);
    tableComponent.getHeader().addColumn("Second Deck", 4, 100);
    tableComponent.setModel(this);  

    // Make the table component visible 
    addAndMakeVisible(tableComponent); 

    // Load the playlist 
    loadPlayList();
}

MusicLibraryManager::~MusicLibraryManager()
{
    // R3E: The music library persists so that it is restored 
    // when the user exits then restarts the application
    saveTracksToPlayList();
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
            g.drawText(trackList[rowNumber].getFileName(),
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

void MusicLibraryManager::saveTracksToPlayList()
{
    // Playlist file csv creation 
    std::ofstream playList("playList.csv");

    // save library to file
    for (unsigned int i = 0; i < trackList.size(); ++i)
    {
        playList << trackList[i].getFileName() << "," << trackList[i].getFileLength() << "\n";
    }
}

void MusicLibraryManager::loadPlayList()
{
    std::ifstream loadedPlayList("playList.csv");
    std::string filePath;
    std::string fileLength;

    // Read data, line by line
    if (loadedPlayList.is_open())
    {
        while (std::getline(loadedPlayList, filePath, ',')) 
        {
            juce::File file{filePath};
            TrackFile trackFile{file};

            std::getline(loadedPlayList, fileLength);
            trackFile.getFileLength() = fileLength;
            trackList.push_back(trackFile);
        }
    }

    // close the play list 
    loadedPlayList.close();
} 

void MusicLibraryManager::populateTrackList(juce::File file)
{
    TrackFile trackFile{file};
    juce::URL audioURL{file};

    trackFile.setFileLength(getAudioLength(audioURL));

    trackList.push_back(trackFile);
    tableComponent.updateContent();
}

void MusicLibraryManager::playAudio(ControlDeck* deck)
{
    int selectedRow{tableComponent.getSelectedRow()};

    if(selectedRow != -1)
    {
        //deck->loadFile(trackList[selectedRow]);
    }
}

juce::String MusicLibraryManager::getAudioLength(juce::URL audioURL)
{
    djAudioPlayer->loadURL(audioURL);
    //double seconds{ djAudioPlayer->getLengthInSeconds() };
    //juce::String minutes{ secondsToMinutes(seconds) };
    //return minutes;
    return "";
}

juce::String secondsToMinutes(double seconds)
{
    //find seconds and minutes and make into string
    int secondsRounded{ int(std::round(seconds)) };
    juce::String min{ std::to_string(secondsRounded / 60) };
    juce::String sec{ std::to_string(secondsRounded % 60) };

    if (sec.length() < 2) // if seconds is 1 digit or less
    {
        //add '0' to seconds until seconds is length 2
        sec = sec.paddedLeft('0', 2);
    }
    return juce::String{ min + ":" + sec };
}