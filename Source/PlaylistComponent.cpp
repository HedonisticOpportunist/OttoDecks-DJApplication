/*
  ==============================================================================

    PlaylistComponent.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

PlaylistComponent::PlaylistComponent(
    DJAudioPlayer* _player,
    AudioFormatManager& formatManagerToUse)
{
    // make buttons visible 
    addAndMakeVisible(loadButton);
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

// R4C: GUI layout includes the music library component from R3
void PlaylistComponent::paint (juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::beige);
    graphics.drawRect (getLocalBounds(), 1);   
    graphics.setColour (juce::Colours::white);
}

void PlaylistComponent::resized()
{
    double rowH = getHeight() / 2;

    tableComponent.setBounds(0, 0, getWidth(), rowH * 1.0);
    loadButton.setBounds(0, rowH * 1.0, getWidth(), rowH * 1.0);
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
        g.fillAll(Colours::lavenderblush);
    }
    else {
        g.fillAll(Colours::aquamarine);
    }
}

void PlaylistComponent::paintCell(Graphics& g,
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

    // R3A: Component allows the user to add files to their library
    if (button == &loadButton)
    {
        auto dlgFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;
        this->chooser.launchAsync(dlgFlags, [this](const juce::FileChooser& chooser)
            {
                auto fileUri = chooser.getURLResult();
                player->loadURL(fileUri);
            });
    }
}

bool PlaylistComponent::isInterestedInFileDrag(const StringArray& files)
{
    return true;  
}

void PlaylistComponent::filesDropped(const StringArray& files, int x, int y)
{
    for (String filename : files)
    {
        return;
    }
}
