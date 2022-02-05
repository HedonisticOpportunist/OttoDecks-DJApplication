/*
  ==============================================================================

    PlayListComponent.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

PlayListComponent::PlayListComponent(ControlDeck* _deck1, ControlDeck* _deck2, DJAudioPlayer* _metaData)
    : deck1(_deck1), deck2(_deck2), metaData(_metaData)
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

PlayListComponent::~PlayListComponent()
{
    saveTracks();
}

void PlayListComponent::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::beige);
    graphics.drawRect(getLocalBounds(), 1);
    graphics.setColour(juce::Colours::white);
}

void PlayListComponent::resized()
{
    searchField.setBounds(0, 0, getWidth(), getHeight() / 10);
    playListTable.setBounds(0, getHeight() * 1 / 10, getWidth(), getHeight() * 4 / 5);
    playListTable.getHeader().setColumnWidth(1, getWidth() / 4);
    playListTable.getHeader().setColumnWidth(2, getWidth() / 4);
}

int PlayListComponent::getNumRows()
{
    return tracks.size();
}

void PlayListComponent::paintRowBackground(juce::Graphics& graphics,
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

void PlayListComponent::paintCell(juce::Graphics& g,
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

juce::Component* PlayListComponent::refreshComponentForCell(int rowNumber,
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
void PlayListComponent::addTrackToPlayerOne()
{
    int selectedRow = playListTable.getSelectedRow();

    if (selectedRow != -1)
    {
        deck1->loadDroppedTrack(tracks[selectedRow].getFileURL());
    }
}

// R3D: Component allows the user to load files from the library into a deck
void PlayListComponent::addTrackToPlayerTwo()
{
    int selectedRow = playListTable.getSelectedRow();

    if (selectedRow != -1)
    {
        deck2->loadDroppedTrack(tracks[selectedRow].getFileURL());
    }
}

void PlayListComponent::addTracksToFile(TrackFile& trackFile)
{
    File file = trackFile.getTrackFileProperties();
    juce::URL audioURL{ file };
    trackFile.setFileLength(getLength(audioURL));
    tracks.push_back(trackFile);
}

//R3B: Component parses and displays meta data such as filenameand song length
juce::String PlayListComponent::getLength(juce::URL audioURL)
{
    metaData->loadURL(audioURL);
    double seconds{ metaData->determineFileLengthInSeconds()};
    juce::String minutes{ convertSecondsToMinutes(seconds)};
    return minutes;
}

juce::String PlayListComponent::convertSecondsToMinutes(double seconds)
{
    int secondsRounded{ int(std::round(seconds)) };
    juce::String min{ std::to_string(secondsRounded / 60) };
    juce::String sec{ std::to_string(secondsRounded % 60) };

    if (sec.length() < 2)
    {
        sec = sec.paddedLeft('0', 2);
    }

    return juce::String{ min + ":" + sec };
}

void PlayListComponent::saveTracks()
{
    std::ofstream tracksToSave("tracks.txt.");

    // save library to file
    for (TrackFile& track : tracks)
    {
        tracksToSave << track.getTrackFileProperties().getFullPathName() << "," << track.getFileLength() << "\n";
    }
}

void PlayListComponent::loadTracks()
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
void PlayListComponent::searchThePlaylist(juce::String inputText)
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

void PlayListComponent::deleteTrack()
{
    tracks.clear();
    playListTable.updateContent();
    playListTable.repaint();
}