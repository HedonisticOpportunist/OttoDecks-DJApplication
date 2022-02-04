/*
  ==============================================================================

    PlaylistComponent.h
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

class PlaylistComponent : public juce::Component,
    public juce::TableListBoxModel,
    public juce::Button::Listener,
    public juce::TextEditor::Listener
{
public:
    PlaylistComponent();

    ~PlaylistComponent() override;

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

    void buttonClicked(juce::Button* button) override;

    void populateTrackListTable(juce::Array<juce::File> files);

    bool checkIfTrackHasBeenLoaded();

    void saveTracks();

    void loadTracks();

    void loadInTracks();

    std::string secondsToMinutes(double seconds);

    void searchPlaylist(juce::String inputText);

private:

    // 
    juce::TableListBox playList;
    std::vector<TrackFile> trackList;

    // Search Field 
    juce::TextEditor searchField;
    //TrackFile& trackFile; 

    // Buttons 
    juce::TextButton importButton{ "IMPORT TRACK FILE" };

    juce::FileChooser chooser{ "Browse audio file" };
    URL audioURL;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};