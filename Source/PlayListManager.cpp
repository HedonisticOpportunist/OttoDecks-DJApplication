/*
  ==============================================================================

    PlaylistComponent.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistManager.h"

PlaylistComponent::PlaylistComponent()
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

    addAndMakeVisible(importButton);
    addAndMakeVisible(playList);
    addAndMakeVisible(searchField);

    searchField.addListener(this);
    importButton.addListener(this);

    // Search field behaviour
    searchField.onTextChange = [this] {searchPlaylist(searchField.getText());};
    searchField.onEscapeKey = [this] {searchField.clear(); playList.deselectAllRows();};

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
    searchField.setBounds(0, 0, getWidth(), getHeight() / 10);

    playList.setBounds(0, getHeight() * 1 / 10, getWidth(), getHeight() * 4 / 5);
    playList.getHeader().setColumnWidth(1, getWidth() / 4);
    playList.getHeader().setColumnWidth(2, getWidth() / 4);
    playList.getHeader().setColumnWidth(3, getWidth() / 6);
    playList.getHeader().setColumnWidth(4, getWidth() / 6);
    playList.getHeader().setColumnWidth(5, getWidth() / 6);

    importButton.setBounds(0, getHeight() * 9 / 10, getWidth(), getHeight() / 10);
}

int PlaylistComponent::getNumRows()
{
    return trackList.size();
}

void PlaylistComponent::paintRowBackground(Graphics& graphics,
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

void PlaylistComponent::paintCell(Graphics& graphics,
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

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
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

std::string PlaylistComponent::secondsToMinutes(double seconds)
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

void PlaylistComponent::populateTrackListTable(juce::Array<juce::File> files)
{
    for (juce::File& file : files)
    {
        bool trackExists = checkIfTrackHasBeenLoaded();

        // init audioTrack instance
        TrackFile trackFile{ file };

        //double length = MusicLibraryControlDeck::getTrackLength(player, trackFile.getFileURL());
        //trackFile.setFileLength(secondsToMinutes(length));

        if (!trackExists)
        {
            // save track to to the track list 
            trackList.push_back(trackFile);
        }
    }

    playList.updateContent();
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
    if (button == &importButton)
    {
        loadInTracks();
    }     
}

bool PlaylistComponent::checkIfTrackHasBeenLoaded()
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

void PlaylistComponent::searchPlaylist(juce::String inputText)
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

void PlaylistComponent::saveTracks()
{
    std::ofstream savedTracksFile;
    savedTracksFile.open("tracks_file.txt");

    for (TrackFile& track : trackList)
    {
        savedTracksFile << track.getTrackFileProperties().getFullPathName() << std::endl;
    }

    savedTracksFile.close();
}

void PlaylistComponent::loadTracks()
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

// R3A: Component allows the user to add files to their library
void PlaylistComponent::loadInTracks()
{
    // initialise the file and select the filters that it is limited to
    juce::String filters = "*.mp3";
    Array<File> file;

    //initialize file chooser
    juce::FileChooser chooser{ "Select files" };
    if (chooser.browseForMultipleFilesToOpen())
    {
        juce::Array<juce::File> trackFiles = chooser.getResults();

        // add the track file to the update tracks method 
        // in the Music Library Manager component 
        populateTrackListTable(trackFiles);

    }
}