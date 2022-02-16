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
                     public juce::TextEditor::Listener
{
public:

    /** The SearchField constructor */
    SearchField(PlayListManager* _playlistManager);

    /** The SearchField destructor */
    ~SearchField() override;

    /** Paints on the screen */
    void paint (juce::Graphics&) override;

    /** Resizes the screen */
    void resized() override;

private:

    // background image 
    Image catImage;

    // Search Field
    juce::TextEditor searchField;
    
    // Pointer to the PlayListManager component 
    PlayListManager* playListManager; 

    /**  PRIVATE METHODS **/

    /** Changes text when searching */
    void changeTextWhenSearching();

    /** Sets up the search field and its respective properties */
    void setUpSearchFieldProperties();

    /** Clears the search list */
    void clearTextAfterSearch();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SearchField)
};
