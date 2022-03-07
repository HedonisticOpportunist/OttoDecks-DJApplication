/*
  ==============================================================================

    PlayListManager.cpp
    Author: @anita.pal

    The implementation of the PlayListManager component. 
  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayListManager.h"

PlayListManager::PlayListManager(AudioMetaData* _audioMetaData, ControlDeck* _deck1, 
    ControlDeck* _deck2): audioMetaData(_audioMetaData), deck1(_deck1), deck2(_deck2)
{
    // Make the playlist table visible 
    addAndMakeVisible(playListTable);

    // PLAYLIST COLUMNS
    playListTable.getHeader().addColumn("Track Title", 1, 100);
    playListTable.getHeader().addColumn("Track Duration", 2, 100);
    playListTable.setModel(this);

    // Load the playlist txt file 
    loadTracksFile();
}

PlayListManager::~PlayListManager()
{
    // Save the playlist 
    saveTracksFile();
}

void PlayListManager::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::beige);
    graphics.drawRect(getLocalBounds(), 1);
    graphics.setColour(juce::Colours::white);
}

void PlayListManager::resized()
{
    playListTable.setBounds(0, getHeight() * 1 / 10, getWidth(), getHeight() * 4 / 5);
    playListTable.getHeader().setColumnWidth(1, getWidth() / 4);
    playListTable.getHeader().setColumnWidth(2, getWidth() / 4);
}

int PlayListManager::getNumRows()
{
    return trackList.size();
}

void PlayListManager::paintRowBackground(juce::Graphics& graphics,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected
)
{
    if (rowIsSelected)
    {
        graphics.fillAll(juce::Colours::mediumseagreen);
    }

    else
    {
        graphics.fillAll(juce::Colours::mediumaquamarine);
    }
}

void PlayListManager::paintCell(juce::Graphics& g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected
)
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

        if (columnId == 2)
        {
            g.drawText(trackList[rowNumber].getFileLength(),
                2,
                0,
                width - 4,
                height,
                juce::Justification::centred,
                true
            );
        }
    }
}

juce::Component* PlayListManager::refreshComponentForCell(int rowNumber,
    int columnId,
    bool isRowSelected,
    Component* existingComponentToUpdate)
{
    if (columnId == 0 ) 
    {
        jassert(existingComponentToUpdate == nullptr);
        return nullptr;
    }

    return existingComponentToUpdate;
}

void PlayListManager::addTrackToPlayerOne()
{
    int selectedRow = playListTable.getSelectedRow();

    if (selectedRow != -1)
    {
        deck1->loadDroppedTrack(trackList[selectedRow].getFileURL());
    }
}

void PlayListManager::addTrackToPlayerTwo()
{
    int selectedRow = playListTable.getSelectedRow();

    if (selectedRow != -1)
    {
        deck2->loadDroppedTrack(trackList[selectedRow].getFileURL());
    }
}

void PlayListManager::addTrackToTracksVector(TrackFile& trackFile)
{
    File file = trackFile.getTrackFileProperties(); // get file specific properties  
    juce::URL audioURL{ file }; // get the url 
    trackFile.setFileLength(audioMetaData->getAudioTrackLength(audioURL)); // set the file length 
    trackList.push_back(trackFile);

    // update the table 
    playListTable.updateContent();
}

void PlayListManager::saveTracksFile()
{
    std::ofstream tracksToSave("tracks.txt.");

    // Save library to the tracks.txt file
    for (TrackFile& track : trackList)
    {
        // determine the format of how the file is saved 
        tracksToSave << track.getTrackFileProperties().getFullPathName() << "," << track.getFileLength() << "\n";
    }
}

void PlayListManager::loadTracksFile()
{
    std::ifstream savedTracks("tracks.txt");
    std::string filePath;
    std::string length;

    if (savedTracks.is_open())
    {
        while (std::getline(savedTracks, filePath, ','))
        {
            juce::File file{ filePath };
            TrackFile track{ file };

            std::getline(savedTracks, length);
            
            // Convert the length string to a juce string 
            track.setFileLength(juce::String(length));

            trackList.push_back(track);
        }
    }

    savedTracks.close();

    // Update the table to represent the contents of the txt file 
    playListTable.updateContent();
}

void PlayListManager::searchThePlaylist(juce::String& inputtedText)
{
    int matchingTrackTitleId = 0;

    for (unsigned int i = 0; i < trackList.size(); ++i)
    {
        if (trackList[i].getTrackFileProperties().getFileName().contains(inputtedText) || trackList[i].getTrackFileProperties().getFileName() == inputtedText)
        {
            matchingTrackTitleId = i; // if there is a match, assign the variable to the counter's value 
            playListTable.selectRow(matchingTrackTitleId); // select the row which matches the value of matchingTrackTitleId
            break;
        }
    }
}

void PlayListManager::deleteTracksFromTable()
{
    // Clear the tracks vector 
    trackList.clear();

    // Update the table 
    playListTable.updateContent();
    playListTable.repaint();
}

void PlayListManager::deselectAllRowsFromTheTable()
{
    playListTable.deselectAllRows(); 
}