/*
  ==============================================================================

    PlayListComponent.h
    Author:  anita.pal

  ==============================================================================
*/
#pragma once
#include <JuceHeader.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include "TrackFile.h"
#include "ControlDeck.h"
#include "DJAudioPlayer.h"

class PlaylistComponent : public juce::Component,
    public juce::TableListBoxModel
{
public:

    PlaylistComponent(ControlDeck* _deck1, ControlDeck* _deck2, DJAudioPlayer* _metaData);

    ~PlaylistComponent() override;

    void paint(juce::Graphics&) override;

    void resized() override;

    int getNumRows() override;

    void paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;

    void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;

    void addTracksToFile(TrackFile& trackFile);

    void addTrackToPlayerOne();

    void addTrackToPlayerTwo();

private:

    // Tracks 
    std::vector<TrackFile> tracks;
    juce::TableListBox playListTable;
    DJAudioPlayer* metaData;

    // Control Decks 
    ControlDeck* deck1;
    ControlDeck* deck2;

    juce::String getLength(juce::URL audioURL);
    juce::String secondsToMinutes(double seconds);

    void saveTracks();
    void loadTracks();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
