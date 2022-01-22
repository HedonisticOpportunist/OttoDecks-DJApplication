/*
  ==============================================================================

    DeckGui.cpp
    Created: 21 Jan 2022 8:46:01pm
    Author:  anita.pal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGui.h"

//==============================================================================
DeckGui::DeckGui(
    DJAudioPlayer* _player, 
    AudioFormatManager& formatManagerToUse,
AudioThumbnailCache& cacheToUse) : 
    player(_player), 
   waveformDisplay(formatManagerToUse, cacheToUse) 
{
    // make buttons and slider visible 
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(waveformDisplay);

    // add the listener events 
    playButton.addListener(this);
    stopButton.addListener(this);
    volumeSlider.addListener(this);
    positionSlider.addListener(this);
    speedSlider.addListener(this);
    loadButton.addListener(this);

    // set ranges for the slider 
    volumeSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    positionSlider.setRange(0.0, 1.0);

    startTimer(500);
   
}

DeckGui::~DeckGui()
{
    stopTimer();
}

void DeckGui::paint (juce::Graphics& g)
{
    g.fillAll(Colour(255, 253, 222));
    g.setColour(Colour(231, 251, 190));
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(Colours::white);
    g.setFont(14.0f);
    g.drawText("", getLocalBounds(),
        Justification::centred, true);   // draw some placeholder text
}

void DeckGui::resized()
{
    double rowH = getHeight() / 8;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    volumeSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    positionSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);
    loadButton.setBounds(0, rowH * 7, getWidth(), rowH);
}

void DeckGui::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        player->setPosition(0);
        player->play();
    }
    
    if (button == &stopButton)
    {
         player->stop();
    }
    
    if (button == &loadButton)
    {
        auto dlgFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;
        this->chooser.launchAsync(dlgFlags, [this](const juce::FileChooser& chooser)
        {
                auto fileUri = chooser.getURLResult();
                player->loadURL(fileUri);
                waveformDisplay.loadURL(fileUri);
        });
    }
}

void DeckGui::sliderValueChanged(Slider* slider)
{
    if (slider == &volumeSlider)
    {
        player->setGain(slider->getValue());
    }
    if (slider == &positionSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
}

bool DeckGui::isInterestedInFileDrag(const StringArray& files)
{
    DBG("DeckGUI::isInterestedInFileDrag");
    return true;
}

void DeckGui::filesDropped(const StringArray& files, int x, int y)
{
    for (String filename : files)
    {
        DBG("DeckGUI::filesDropped " << filename);
        URL fileURL = URL{ File{filename} };
        player->loadURL(fileURL);
        return;
    }
}

void DeckGui::timerCallback()
{
    DBG("DeckGUI::timerCallback");
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}
