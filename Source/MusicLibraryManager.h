/*
  ==============================================================================

    MusicLibraryManager.h
    Author:  anita.pal

  ==============================================================================
*/

#pragma once
#include "ControlDeck.h"
#include "DJAudioPlayer.h"
#include <fstream>
#include <JuceHeader.h>
#include "TrackFile.h"

class MusicLibraryManager  : public juce::Component,
                             public TableListBoxModel,
                             public Button::Listener
{
public:

    /** The Playlist constructor */
    MusicLibraryManager();

    /** The Playlist Component destructor */
    ~MusicLibraryManager() override;

    /** Paints on the screen */
    void paint (juce::Graphics&) override;

    /** Resizes the screen */
    void resized() override;

    /** Gets the number of rows */
    int getNumRows() override;

    /** Deals with button clicks */
    void buttonClicked(Button* button) override;

    /** Paints the row background */
    void paintRowBackground(Graphics&,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected) override;

    /** Paints the cell */
    void paintCell(Graphics&,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;

    /** Refreshes the component for each cell */
    Component* refreshComponentForCell(int rowNumber,
        int columnId,
        bool isRowSelected,
        Component* existingComponentToUpdate) override;

    /** Update the tracklist vector */
    void saveTracksToPlayList();

    void loadPlayList(); 

    void populateTrackList(juce::File file);

private:

    TableListBox tableComponent;
    std::vector<TrackFile> trackList;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicLibraryManager)
};
