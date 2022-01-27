/*
  ==============================================================================

    ControlDeck.cpp
    Author: anita.pal

  ==============================================================================
*/

#include "ControlDeck.h"
#include <JuceHeader.h>

ControlDeck::ControlDeck
(
    DJAudioPlayer* _player, 
    AudioFormatManager& formatManagerToUse, 
    AudioThumbnailCache& cacheToUse) : player(_player), waveformDisplay(formatManagerToUse, cacheToUse) 
{
    // make the buttons visible 
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    // make the sliders visible 
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(waveformDisplay);

    // add the listener events to the buttons
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    // add the listener events to the sliders 
    volumeSlider.addListener(this);
    positionSlider.addListener(this);
    speedSlider.addListener(this);
   
    // change the look of the sliders
    getLookAndFeel().setColour(juce::Slider::trackColourId, juce::Colours::lightcoral); 

    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::honeydew);
    volumeSlider.setSliderStyle(juce::Slider::Rotary);
    positionSlider.setSliderStyle(juce::Slider::Rotary);
    speedSlider.setSliderStyle(juce::Slider::Rotary);

    // set ranges for the slider 
    volumeSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    positionSlider.setRange(0.0, 1.0);

    startTimer(500);
   
}

ControlDeck::~ControlDeck()
{
    stopTimer();
}

void ControlDeck::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   
    g.setColour(juce::Colours::peachpuff);
    g.drawRect(getLocalBounds(), 1);   

    //A call to the buttons and sliders painting functions
    repaintButtons(); 
    repaintSliders(); 
}

void ControlDeck::resized()
{
    double rowH = getHeight() / 8.0;  

    // button positions
    playButton.setBounds(0, 0, getWidth(), rowH * 1.0); 
    stopButton.setBounds(0, rowH * 1.0, getWidth(), rowH * 1.0);
    loadButton.setBounds(0, rowH * 2.0, getWidth(), rowH * 1.0);

    // slider positions 
    volumeSlider.setBounds(0, rowH * 3.0, getWidth(), rowH * 1.0);
    positionSlider.setBounds(0, rowH * 4.0, getWidth(), rowH * 1.0);
    speedSlider.setBounds(0, rowH * 5.0, getWidth(), rowH * 1.0);

    // wave form display 
    waveformDisplay.setBounds(0, rowH  * 6.0, getWidth(), rowH * 1.0);
}

void ControlDeck::repaintButtons()
{
    if (playButton.isOver())
    {
        playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkblue);
    }

    else
    {
        playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkslateblue);
    }

    if (stopButton.isOver())
    {
        stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkorchid);
    }

    else 
    {
        stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkturquoise);
    }

    if (loadButton.isOver())
    {
        loadButton.setColour(juce::TextButton::buttonColourId, juce::Colours::blanchedalmond);
    }

    else
    {
        loadButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkorange);
    }
}

void ControlDeck::repaintSliders()
{
    if (volumeSlider.isMouseOver() || positionSlider.isMouseOver() || speedSlider.isMouseOver())
    {
        getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::lavender);
    }

    else
    {
        getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::aquamarine);
    }
}

void ControlDeck::buttonClicked(Button* button)
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

void ControlDeck::sliderValueChanged(Slider* slider)
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

bool ControlDeck::isInterestedInFileDrag(const StringArray& files)
{
    return true;
}

void ControlDeck::filesDropped(const StringArray& files, int x, int y)
{
    for (String filename : files)
    {
        URL fileURL = URL{ File{filename} };
        player->loadURL(fileURL);
        return;
    }
}

void ControlDeck::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}
