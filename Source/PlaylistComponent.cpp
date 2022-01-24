/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 22 Jan 2022 2:15:06pm
    Author:  anita.pal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

PlaylistComponent::PlaylistComponent()
{
    addAndMakeVisible(tableComponent);
    tableComponent.getHeader().addColumn("Track title", 1, 400);
    tableComponent.getHeader().addColumn("", 2, 200);

    tableComponent.setModel(this);

    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   

    g.setColour (juce::Colours::beige);
    g.drawRect (getLocalBounds(), 1);   
    g.setColour (juce::Colours::white);
}

void PlaylistComponent::resized()
{
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int PlaylistComponent::getNumRows()
{
    return trackTitles.size();
}

void PlaylistComponent::paintRowBackground(Graphics& g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else {
        g.fillAll(Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell(Graphics& g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected)
{
    g.drawText(trackTitles[rowNumber], 
        2, 0,
        width - 4, height,
        Justification::centredLeft,
        true);
}

Component* PlaylistComponent::refreshComponentForCell(
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

void PlaylistComponent::buttonClicked(Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());
    DBG("PlaylistComponent::buttonClicked " << trackTitles[id]);
}
