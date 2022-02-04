/*
  ==============================================================================

    PlayListManager.h
    Author:  Anita

  ==============================================================================
*/

#pragma once
#include "DJAudioPlayer.h"
#include <JuceHeader.h>
#include "MusicControlDeck.h"
#include "TrackFile.h"
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdio.h>

class PlayListManager : public juce::Component,
                          public juce::TableListBoxModel,
                          public juce::Button::Listener,
                          public juce::TextEditor::Listener
{
public:
    PlayListManager();

    ~PlayListManager() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;

    void paintRowBackground(Graphics& g,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected) override;

    void paintCell(Graphics& g,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;

    juce::Component* refreshComponentForCell(int rowNumber,
        int columnId,
        bool isRowSelected,
        juce::Component* existingComponentToUpdate) override;

    void buttonClicked(Button* button) override;

  private:

    // Tracks
    juce::TableListBox playList;
    std::vector<TrackFile> trackList;

    // Search Field 
    juce::TextEditor searchField;
    
    void saveTracks();

    void loadTracks();

    void populateTrackListTable();

    std::string secondsToMinutes(double seconds);

    void searchPlaylist(juce::String inputText);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayListManager)
};