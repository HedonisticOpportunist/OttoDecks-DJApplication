/*
  ==============================================================================

    PlayListManager.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayListManager.h"

PlayListManager::PlayListManager(AudioMetaData* _audioMetaData, ControlDeck* _deck1, ControlDeck* _deck2)
    : audioMetaData(_audioMetaData), deck1(_deck1), deck2(_deck2)
{
    // make the playlist table visible 
    addAndMakeVisible(playListTable);

    // PLAYLIST COLUMNS
    playListTable.getHeader().addColumn("Track Title", 1, 100);
    playListTable.getHeader().addColumn("Track Duration", 2, 100);
    playListTable.setModel(this);

    // SEARCH FIELD
    addAndMakeVisible(searchField);
    searchField.applyFontToAllText(juce::Font{ 12.0f });
    searchField.setJustification(juce::Justification::centred);

    searchField.setTextToShowWhenEmpty("SEARCH PLAYLIST (ESC KEY TO CLEAR)", juce::Colours::lightpink);
    searchField.setInputRestrictions(24);
    searchField.addListener(this);

    searchField.onTextChange = [this] {searchThePlaylist(searchField.getText());};
    searchField.onEscapeKey = [this] {searchField.clear(); playListTable.deselectAllRows();};


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
    playListTable.setBounds(0, getHeight() * 1 / 10, getWidth(), getHeight() * 4 / 5);
    playListTable.getHeader().setColumnWidth(1, getWidth() / 4);
    playListTable.getHeader().setColumnWidth(2, getWidth() / 4);
}

int PlayListManager::getNumRows()
{
    return tracks.size();
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
        graphics.fillAll(juce::Colours::orchid);
    }
    else
    {
        graphics.fillAll(juce::Colours::lightgreen);
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
            g.drawText(tracks[rowNumber].getFileName(),
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
            g.drawText(tracks[rowNumber].getFileLength(),
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

// R3D: Component allows the user to load files from the library into a deck
void PlayListManager::addTrackToPlayerOne()
{
    int selectedRow = playListTable.getSelectedRow();

    if (selectedRow != -1)
    {
        deck1->loadDroppedTrack(tracks[selectedRow].getFileURL());
    }
}

// R3D: Component allows the user to load files from the library into a deck
void PlayListManager::addTrackToPlayerTwo()
{
    int selectedRow = playListTable.getSelectedRow();

    if (selectedRow != -1)
    {
        deck2->loadDroppedTrack(tracks[selectedRow].getFileURL());
    }
}

void PlayListManager::addTracksToFile(TrackFile& trackFile)
{
    File file = trackFile.getTrackFileProperties();
    juce::URL audioURL{ file };
    trackFile.setFileLength(audioMetaData->getAudioTrackLength(audioURL));
    tracks.push_back(trackFile);
}

void PlayListManager::saveTracks()
{
    std::ofstream tracksToSave("tracks.txt.");

    // save library to file
    for (TrackFile& track : tracks)
    {
        tracksToSave << track.getTrackFileProperties().getFullPathName() << "," << track.getFileLength() << "\n";
    }
}

void PlayListManager::loadTracks()
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
            track.setFileLength(length);
            tracks.push_back(track);
        }
    }

    savedTracks.close();
    playListTable.updateContent();
}

// R3C: Component allows the user to search for files
void PlayListManager::searchThePlaylist(juce::String inputText)
{
    int matchingTrackTitleId;

    for (int i = 0; i < tracks.size(); ++i)
    {
        if (tracks[i].getFileName().contains(inputText))
        {
            matchingTrackTitleId = i;
        }

        playListTable.selectRow(matchingTrackTitleId);
    }
}

void PlayListManager::deleteTracks()
{
    tracks.clear();
    playListTable.updateContent();
    playListTable.repaint();
}