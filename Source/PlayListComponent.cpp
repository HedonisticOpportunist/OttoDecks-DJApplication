/*
  ==============================================================================

    PlayListComponent.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

PlaylistComponent::PlaylistComponent(ControlDeck* _deck1, ControlDeck* _deck2, DJAudioPlayer* _metaData) 
    : deck1(_deck1), deck2(_deck2), metaData(_metaData)
{
    // make the playlist table visible 
    addAndMakeVisible(playListTable);

    playListTable.getHeader().addColumn("Track Title", 1, 100);
    playListTable.getHeader().addColumn("Track Duration", 2, 100);
    playListTable.setModel(this);

    loadTracks();
}

PlaylistComponent::~PlaylistComponent()
{
    saveTracks();
}

void PlaylistComponent::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::beige);
    graphics.drawRect(getLocalBounds(), 1);
    graphics.setColour(juce::Colours::white);
}

void PlaylistComponent::resized()
{
    playListTable.setBounds(0, getHeight() * 1 / 10, getWidth(), getHeight() * 4 / 5);
    playListTable.getHeader().setColumnWidth(1, getWidth() / 4);
    playListTable.getHeader().setColumnWidth(2, getWidth() / 4);
}

int PlaylistComponent::getNumRows()
{
    return tracks.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics& graphics,
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

void PlaylistComponent::paintCell(juce::Graphics& g,
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

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
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
void PlaylistComponent::addTrackToPlayerOne()
{
    int selectedRow = playListTable.getSelectedRow();

    if (selectedRow != -1)
    {
        deck1->loadDroppedTrack(tracks[selectedRow].getFileURL());
    }
}

// R3D: Component allows the user to load files from the library into a deck
void PlaylistComponent::addTrackToPlayerTwo()
{
    int selectedRow = playListTable.getSelectedRow();

    if (selectedRow != -1)
    {
        deck2->loadDroppedTrack(tracks[selectedRow].getFileURL());
    }
}

void PlaylistComponent::addTracksToFile(TrackFile& trackFile)
{
    File file = trackFile.getTrackFileProperties();
    juce::URL audioURL{ file };
    trackFile.setFileLength(getLength(audioURL));
    tracks.push_back(trackFile);
}

juce::String PlaylistComponent::getLength(juce::URL audioURL)
{
    metaData->loadURL(audioURL);
    double seconds{ metaData->getLengthInSeconds() };
    juce::String minutes{ secondsToMinutes(seconds) };
    return minutes;
}

juce::String PlaylistComponent::secondsToMinutes(double seconds)
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

void PlaylistComponent::saveTracks()
{
    std::ofstream tracksToSave("tracks.txt.");

    // save library to file
    for (TrackFile& track : tracks)
    {
        tracksToSave << track.getTrackFileProperties().getFullPathName() << "\n";
    }
}

void PlaylistComponent::loadTracks()
{
    std::ifstream savedTracks("tracks.txt");
    std::string filePath;
    std::string length;

    if (savedTracks.is_open())
    {
        while (savedTracks) 
        {
            
            std::getline(savedTracks, filePath);
            
            if (filePath != "")
            {
                juce::File file{ filePath };
                TrackFile track{ file };
                tracks.push_back(track);
            }
        }
    }

    savedTracks.close();
    playListTable.updateContent();
}