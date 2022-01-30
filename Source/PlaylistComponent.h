/*
  ==============================================================================

    PlaylistComponent.h
    Author:  anita.pal

  ==============================================================================
*/

#pragma once
#include "DJAudioPlayer.h"
#include <JuceHeader.h>

class PlaylistComponent  : public juce::Component,
                           public TableListBoxModel,
                           public FileDragAndDropTarget,
                           public Button::Listener
{
public:

    /** The Playlist constructor */
    PlaylistComponent(DJAudioPlayer* _player, AudioFormatManager& formatManagerToUse);

    /** The Playlist Component destructor */
    ~PlaylistComponent();

    /** Paints on the screen */
    void paint (juce::Graphics&) override;

    /** Resizes the screen */
    void resized() override;

    /** Gets the number of rows */
    int getNumRows() override;

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

    /** Checks what happens when button is clicked */
    void buttonClicked(Button* button) override;

    /** Allows drag and drop */
    bool isInterestedInFileDrag(const StringArray& files) override;

    /** Allows files to be dropped */
    void filesDropped(const StringArray& files, int x, int y) override;

private:

    // private members of the class 
    TextButton loadButton{ "Load" };
    juce::FileChooser chooser{ "Browse audio file"};
    DJAudioPlayer* player;

    TableListBox tableComponent;
    std::vector<std::string> trackTitles;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
