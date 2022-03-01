/*
  ==============================================================================

    SearchField.h
    Author:  anita.pal

    The search field component displays a search field. 
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PlayListManager.h"

class SearchField  : public juce::Component,
                     public juce::Button::Listener, 
                     public juce::TextEditor::Listener
{
public:

    /** The SearchField constructor */
    SearchField(PlayListManager* _playlistManager);

    /** The SearchField destructor */
    ~SearchField() override;

    /** Deals with button clicks */
    void buttonClicked(Button* button) override;

    /** Paints on the screen */
    void paint (juce::Graphics&) override;

    /** Resizes the screen */
    void resized() override;

private:

    // background image 
    Image catImage;

    // Search Field
    juce::TextEditor searchField;

    // Search Field button 
    TextButton searchButton{"Search"};
    TextButton clearButton{"Clear Row"};
    
    // Pointer to the PlayListManager component 
    PlayListManager* playListManager; 

    /**  PRIVATE METHODS **/

    /** Changes text when searching */
    void searchThroughPlaylist();

    /** Sets up the search field and its respective properties */
    void setUpSearchFieldProperties();

    /** Clears the search list */
    void clearTextAfterSearch(); 

    /** Deselects the playlist row */
    void deselectRow();

    /** Repaints the search and clear buttons */
    void repaintButtons();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SearchField)
};
