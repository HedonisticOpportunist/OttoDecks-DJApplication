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
DeckGui::DeckGui(DJAudioPlayer* _djAudioPlayer) : djAudioPlayer{ _djAudioPlayer}
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(speedSlider);

    playButton.addListener(this);
    stopButton.addListener(this);
    volumeSlider.addListener(this);
    positionSlider.addListener(this);
    speedSlider.addListener(this);
    loadButton.addListener(this);
}

DeckGui::~DeckGui()
{
}

void DeckGui::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(Colour(0xff3f3f3f));
    g.setColour(juce::Colours::lightpink);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::whitesmoke);
    g.setFont (14.0f);
    g.drawText ("", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    float rowH = getWidth() / 6;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    volumeSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    positionSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    loadButton.setBounds(0, rowH * 5, getWidth(), rowH);
}

void DeckGui::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        djAudioPlayer->setPosition(0);
        djAudioPlayer->play();
    }
    
    if (button == &stopButton)
    {
         djAudioPlayer->stop();
    }
    
    if (button == &loadButton)
    {
        auto dlgFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;
        this->chooser.launchAsync(dlgFlags, [this](const juce::FileChooser& chooser)
        {
                auto fileUri = chooser.getURLResult();
                djAudioPlayer->loadURL(fileUri);
        });
    }
}

void DeckGui::sliderValueChanged(Slider* slider)
{
    if (slider == &volumeSlider)
    {
        djAudioPlayer->setGain(slider->getValue());
    }
    if (slider == &positionSlider)
    {
        djAudioPlayer->setPositionRelative(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        djAudioPlayer->setSpeed(slider->getValue());
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
        djAudioPlayer->loadURL(fileURL);
        return;
    }
}
