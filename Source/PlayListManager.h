/*
  ==============================================================================

    PlayListComponent.h
    Author:  anita.pal

  ==============================================================================
*/
#pragma once
#include "AudioMetaData.h"
#include "ControlDeck.h"
#include <fstream>
#include <JuceHeader.h>
#include "TrackFile.h"
#include <vector>

class PlayListManager : public juce::Component,
                        public juce::TableListBoxModel,
                        public juce::TextEditor::Listener
                          
{
public:

    PlayListManager(AudioMetaData* _audioMetaData, ControlDeck* _deck1, ControlDeck* _deck2);

    ~PlayListManager() override;

    void paint(juce::Graphics&) override;

    void resized() override;

    int getNumRows() override;

    void paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;

    void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;

    void addTracksToFile(TrackFile& trackFile);

    void addTrackToPlayerOne();

    void addTrackToPlayerTwo();

    void deleteTracks();

private:

    // Audio Meta Data
    AudioMetaData* audioMetaData;

    // Tracks 
    std::vector<TrackFile> tracks;
    juce::TableListBox playListTable;
    
    // Control Decks 
    ControlDeck* deck1;
    ControlDeck* deck2;

    // Search Field
    juce::TextEditor searchField;

    /* Private Methods */
    void saveTracks();
    void loadTracks();
    void searchThePlaylist(juce::String inputText);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayListManager)
};
