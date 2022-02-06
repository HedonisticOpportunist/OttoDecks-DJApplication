/*
  ==============================================================================

    PlayListManager.h
    Author: @anita.pal

    This component deals with the management and organisation of the playlist
    table and its respective content. 
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

    /** The PlayListManagger constructor */
    PlayListManager(AudioMetaData* _audioMetaData, ControlDeck* _deck1, ControlDeck* _deck2);

    /** The PlayListManager destructor */
    ~PlayListManager() override;

    /** Adds a track file to a tracks vector */
    void addTrackToTracksVector(TrackFile& trackFile);

    /** Adds the track to the Audio Player One */
    void addTrackToPlayerOne();

    /** Adds the track to the Audio Player Two */
    void addTrackToPlayerTwo();

    /** Deletes tracks from the playlist table */
    void deleteTracksFromTable();

    /** Paints onto the screen */
    void paint(juce::Graphics&) override;

    /** Resizes the screen */
    void resized() override;

    /** Returns the number of rows */
    int getNumRows() override;

    /** Paints the row background */
    void paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;

    /** Paints the cell */
    void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    /** Refreshes the components for the cell */
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;

private:

    // A point to the AudioMetaData class 
    AudioMetaData* audioMetaData;

    // Tracks list vector 
    std::vector<TrackFile> trackList;

    // The playlist table 
    juce::TableListBox playListTable;
    
    // Control Decks 
    ControlDeck* deck1;
    ControlDeck* deck2;

    // Search Field
    juce::TextEditor searchField;

    /* PRIVATE METHODS */
    
    /** Saves the tracks.txt file */
    void saveTracksFile();

    /** Loads the tracks.txt file */
    void loadTracksFile();
    
    /** Searches for the playlist for a specific track */
    void searchThePlaylist(juce::String& inputtedText);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayListManager)
};
