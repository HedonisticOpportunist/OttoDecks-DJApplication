/*
  ==============================================================================

    SearchField.cpp
    Author:  anita.pal

    The implementation of the SearchField component.
  ==============================================================================
*/

#include <JuceHeader.h>
#include "SearchField.h"

SearchField::SearchField(PlayListManager* _playListManager) : playListManager(_playListManager)
{
    // add background image 
    // credit @ https://unsplash.com/@tracamyng
    catImage = ImageCache::getFromMemory(BinaryData::cat_png, BinaryData::cat_pngSize);

    // SEARCH FIELD
    addAndMakeVisible(searchField);
    setUpSearchFieldProperties();
    changeTextWhenSearching(); 
}

SearchField::~SearchField()
{
}

void SearchField::paint (juce::Graphics& graphics)
{
    graphics.drawImage(catImage, getLocalBounds().toFloat());
}

void SearchField::resized()
{
    searchField.setBounds(0, 0, getWidth(), getHeight() / 10);
}

void SearchField::changeTextWhenSearching()
{
    searchField.onTextChange = [this] {playListManager->searchThePlaylist(searchField.getText());};
}

void SearchField::setUpSearchFieldProperties()
{
    searchField.applyFontToAllText(juce::Font{ 14.0f });
    searchField.setJustification(juce::Justification::centred);

    searchField.setTextToShowWhenEmpty("SEARCH THE PLAYLIST (ESC KEY TO CLEAR)", juce::Colours::darkviolet);
    searchField.setInputRestrictions(24);
}

void SearchField::clearTextAfterSearch()
{
    searchField.onEscapeKey = [this] {searchField.clear(); playListManager->deselectAllRowsFromTheTable();};
}