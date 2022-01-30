/*
  ==============================================================================

    MusicLibraryManager.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MusicLibraryManager.h"

MusicLibraryManager::MusicLibraryManager()
{
    // make table component visible 
    addAndMakeVisible(tableComponent);

    // column and tracks 
    tableComponent.getHeader().addColumn("Track title", 1, 400);
    tableComponent.getHeader().addColumn("", 2, 200);

    tableComponent.setModel(this);

    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
}

MusicLibraryManager::~MusicLibraryManager()
{
}

// R4C: GUI layout includes the music library component from R3
void MusicLibraryManager::paint (juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::beige);
    graphics.drawRect (getLocalBounds(), 1);   
    graphics.setColour (juce::Colours::white);
}

void MusicLibraryManager::resized()
{
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int MusicLibraryManager::getNumRows()
{
    return trackTitles.size();
}

void MusicLibraryManager::paintRowBackground(Graphics& g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::lavenderblush);
    }
    else {
        g.fillAll(Colours::aquamarine);
    }
}

void MusicLibraryManager::paintCell(Graphics& g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected)
{
    if (rowNumber < getNumRows())
    {
        g.drawText(
            trackTitles[rowNumber],
            2, 0,
            width - 4, height,
            Justification::centredLeft,
            true);
    }
}

Component* MusicLibraryManager::refreshComponentForCell(
    int rowNumber,
    int columnId,
    bool isRowSelected,
    Component* existingComponentToUpdate)
{
    String id{ std::to_string(rowNumber) };
   
    if (columnId == 1)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton * btn = new TextButton("play");
            btn->setComponentID(id);
            existingComponentToUpdate = btn;
            btn->addListener(this);
        }
    }
    return existingComponentToUpdate;
}

void MusicLibraryManager::buttonClicked(Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());
    DBG("PlaylistComponent::buttonClicked " << trackTitles[id]);
}