/*
  ==============================================================================

    SearchField.cpp
    Author: @anita.pal

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

    // SEARCH AND CLEAR BUTTON
    addAndMakeVisible(searchButton);
    addAndMakeVisible(clearButton);

    searchButton.addListener(this);
    clearButton.addListener(this);

    // SEARCH FIELD
    addAndMakeVisible(searchField);
    setUpSearchFieldProperties();
    searchThroughPlaylist(); 
}

SearchField::~SearchField()
{
}

void SearchField::buttonClicked(Button* button)
{
    if (button == &searchButton)
    {
        searchThroughPlaylist();
    }

    if (button == &clearButton)
    {
        deselectRow();
    }
}

void SearchField::paint (juce::Graphics& graphics)
{
    graphics.drawImage(catImage, getLocalBounds().toFloat());

    // repaint the search and clear button 
    repaintButtons(); 
}

void SearchField::resized()
{
    double rowH = getHeight() / 10; 

    searchField.setBounds(0, 0, getWidth(), rowH);
    searchButton.setBounds(0, rowH * 1.0, getWidth() / 2, rowH * 1.0);
    clearButton.setBounds(150, rowH * 1.0, getWidth() / 2, rowH * 1.0);
}

void SearchField::searchThroughPlaylist()
{
    juce::String inputString = searchField.getText();
    playListManager->searchThePlaylist(inputString); // playlist pointer that calls the method which performs the searching of the tracks vector 
}

void SearchField::setUpSearchFieldProperties()
{
    searchField.applyFontToAllText(juce::Font{ 14.0f });
    searchField.setJustification(juce::Justification::centred);
    searchField.setTextToShowWhenEmpty("SEARCH THE PLAYLIST", juce::Colours::darkviolet);
    searchField.setInputRestrictions(24);
}

void SearchField::deselectRow()
{
    // de-selects the row with the found track from the playlist table 
    playListManager->deselectAllRowsFromTheTable(); 
}

void SearchField::clearTextAfterSearch()
{
    searchField.onEscapeKey = [this] {searchField.clear(); playListManager->deselectAllRowsFromTheTable();};
}

void SearchField::repaintButtons()
{
    // set the colour for the search button if mouse over OR it has stopped playing 
    if (searchButton.isOver() || searchButton.isMouseOver())
    {
        searchButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkblue);
    }

    // set the colour of the search button when the mouse is not hovering over it 
    else
    {
        searchButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightslategrey);
    }

    // set the colour of the clear button if mouse is over OR it has stopped playing 
    if (clearButton.isOver() || clearButton.isMouseOver())
    {
        clearButton.setColour(juce::TextButton::buttonColourId, juce::Colours::aquamarine);
    }

    // set the colour of the clear button when the mouse is not hovering over it 
    else
    {
        clearButton.setColour(juce::TextButton::buttonColourId, juce::Colours::midnightblue);
    }
}
