/*
  ==============================================================================

    PlaylistComponent.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistManager.h"

PlayListManager::PlayListManager()
{
    // Set the columns 
    playList.getHeader().addColumn("Track Title", 1, 150);
    playList.getHeader().addColumn("Duration", 2, 100);
    playList.getHeader().addColumn("", 3, 100);
    playList.setModel(this);

    // Search field 
    searchField.applyFontToAllText(juce::Font{ 10.0f });
    searchField.setJustification(juce::Justification::centred);
    searchField.setTextToShowWhenEmpty("Search The Track List", juce::Colours::orange);
    searchField.setInputRestrictions(24);

    addAndMakeVisible(playList);
    addAndMakeVisible(searchField);
    searchField.addListener(this);
 
    // Search field behaviour
    searchField.onTextChange = [this] {searchPlaylist(searchField.getText());};
    searchField.onEscapeKey = [this] {searchField.clear(); playList.deselectAllRows();};

    loadTracks();
}

PlayListManager::~PlayListManager()
{
    saveTracks();
}

void PlayListManager::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::beige);
    graphics.drawRect(getLocalBounds(), 1);
    graphics.setColour(juce::Colours::white);
}

void PlayListManager::resized()
{
    searchField.setBounds(0, 0, getWidth(), getHeight() / 10);

    playList.setBounds(0, getHeight() * 1 / 10, getWidth(), getHeight() * 4 / 5);
    playList.getHeader().setColumnWidth(1, getWidth() / 4);
    playList.getHeader().setColumnWidth(2, getWidth() / 4);
    playList.getHeader().setColumnWidth(3, getWidth() / 6);
    playList.getHeader().setColumnWidth(4, getWidth() / 6);
    playList.getHeader().setColumnWidth(5, getWidth() / 6);
}

int PlayListManager::getNumRows()
{
    return trackList.size();
}

void PlayListManager::paintRowBackground(Graphics& graphics,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected)
{
    if (rowIsSelected)
    {
        graphics.fillAll(Colours::lavenderblush);
    }

    else 
    {
        graphics.fillAll(Colours::aquamarine);
    }
}

void PlayListManager::paintCell(Graphics& graphics,
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
            graphics.drawText(trackList[rowNumber].getFileName(),
                2, 0,
                width - 4, height,
                juce::Justification::centredLeft,
                true);
        }

        else if (columnId == 2)
        {
            graphics.drawText(trackList[rowNumber].getFileLength(),
                2, 0,
                width - 4, height,
                juce::Justification::centredLeft,
                true);
        }
    }
}

juce::Component* PlayListManager::refreshComponentForCell(int rowNumber,
    int columnId,
    bool isRowSelected,
    juce::Component* existingComponentToUpdate)
{
    if (columnId == 0)
    {
        jassert(existingComponentToUpdate == nullptr);
        return nullptr;
    }

    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new juce::TextButton{ "Remove Track" };
            juce::String id{ std::to_string(rowNumber) + "_remove" };
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

std::string PlayListManager::secondsToMinutes(double seconds)
{
    // get minutes
    int minutes = int(trunc(seconds / 60.0));

    std::string minStr = std::to_string(minutes);

    // get seconds
    int remainingSeconds = int(seconds) % 60;

    std::string secStr = std::to_string(remainingSeconds);

    // Extend single digit seconds
    if (secStr.length() <= 1)
    {
        secStr = '0' + secStr;
    }
    return minStr + ":" + secStr;
}

void PlayListManager::populateTrackListTable()
{
    //trackList = MusicControlDeck::populateTrackListVector();
    playList.updateContent();
}

void PlayListManager::buttonClicked(juce::Button* button)
{
    // stuff   
}

void PlayListManager::searchPlaylist(juce::String inputText)
{
    int matchingTrackId;

    for (unsigned int i = 0; i < trackList.size(); ++i)
    {
        if (trackList[i].getFileName().contains(inputText))
        {
            matchingTrackId = i;
        }

        playList.selectRow(matchingTrackId);
    }
}

void PlayListManager::saveTracks()
{
    std::ofstream savedTracksFile;
    savedTracksFile.open("tracks_file.txt");

    for (TrackFile& track : trackList)
    {
        savedTracksFile << track.getTrackFileProperties().getFullPathName() << std::endl;
    }

    savedTracksFile.close();
}

void PlayListManager::loadTracks()
{
    std::ifstream savedTracksFile("tracks_file.txt");
    std::string filePath;

    // Parse data
    if (savedTracksFile.is_open())
    {
        while (savedTracksFile) 
        {
            std::getline(savedTracksFile, filePath);
            if (filePath != "")

            {
                juce::File file{ filePath };
                TrackFile track{ file };

                //double length = MusicLibraryControlDeck::getTrackLength(player, track.getFileURL());
                //trackFile.setFileLength(secondsToMinutes(length));

                // push to tracks playlist
                trackList.push_back(track);
            }

        }
    }

    savedTracksFile.close();
    playList.updateContent();
}