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
    AudioThumbnailCache& cacheToUse) : 
    player(_player),
    waveformDisplay(formatManagerToUse, cacheToUse)
{
    // make the buttons visible 
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    addAndMakeVisible(rewindButton);
    addAndMakeVisible(fastForwardButton);
    addAndMakeVisible(loopButton);

    // make the sliders visible 
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(speedSlider);

    // make the waveform visible 
    addAndMakeVisible(waveformDisplay);

    // make the labels visible 
    addAndMakeVisible(volumeLabel);
    addAndMakeVisible(positionLabel);
    addAndMakeVisible(speedLabel);

    // add the listener events to the buttons
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    rewindButton.addListener(this);
    fastForwardButton.addListener(this);
    loopButton.addListener(this);

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

    // adjust the sliders text box position 
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 160, volumeSlider.getTextBoxHeight());
    positionSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 160, volumeSlider.getTextBoxHeight());
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 160, volumeSlider.getTextBoxHeight());

    // adjust the font of the labels
    volumeLabel.setFont(12.0f);
    positionLabel.setFont(12.0f);
    speedLabel.setFont(12.0f);

    // add text to the labels
    volumeLabel.setText("Volume", juce::dontSendNotification);
    positionLabel.setText("Position", juce::dontSendNotification);
    speedLabel.setText("Speed", juce::dontSendNotification);

    // attach the labels to the sliders
    volumeLabel.attachToComponent(&volumeSlider, true);
    positionLabel.attachToComponent(&positionSlider, true);
    speedLabel.attachToComponent(&speedSlider, true);

    startTimer(500);

}

ControlDeck::~ControlDeck()
{
    stopTimer();
}

void ControlDeck::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::darkcyan);
    graphics.setColour(juce::Colours::ghostwhite);
    graphics.drawRect(getLocalBounds(), 0);

    //A call to the buttons and sliders painting functions
    repaintButtons();
    repaintSliders();
}

void ControlDeck::resized()
{
    double rowH = getHeight() / 10.5;

    // Waveform Display 
    waveformDisplay.setBounds(0, 0, getWidth(), rowH * 1);

    // Play, Stop and Load button positions
    playButton.setBounds(0, rowH * 1.0, getWidth(), rowH * 1.0);
    stopButton.setBounds(0, rowH * 2.0, getWidth(), rowH * 1.0);
    loadButton.setBounds(0, rowH * 3.0, getWidth(), rowH * 1.0);

    // Slider Positions 
    volumeSlider.setBounds(50, rowH * 4.2, getWidth(), rowH * 1.5);
    positionSlider.setBounds(50, rowH * 5.2, getWidth(), rowH * 1.5);
    speedSlider.setBounds(50, rowH * 6.2, getWidth(), rowH * 1.5);

    // Rewind, Fastforward and Loop buttons
    rewindButton.setBounds(0, rowH * 7.5, getWidth(), rowH * 1.0);
    fastForwardButton.setBounds(0, rowH * 8.5, getWidth(), rowH * 1.0);
    loopButton.setBounds(0, rowH * 9.5, getWidth(), rowH * 1.0);
}

void ControlDeck::repaintButtons()
{

    // set the colour for the play button if mouse over OR it has stopped playing 
    if (playButton.isOver() || playButton.isMouseOver())
    {
        playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkblue);
    }

    // set the colour of the play button when mouse is not hovering over it 
    else
    {
        playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightslategrey);
    }

    // set the colour of the stop button is mouse is over OR it has stopped playing 
    if (stopButton.isOver() || stopButton.isMouseOver())
    {
        stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::aquamarine);
    }

    // set the colour of the stop button when mouse is not hovering over it 
    else
    {
        stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::midnightblue);
    }

    // set the colour for the load button if mouse over OR it has stopped playing 
    if (loadButton.isOver() || loadButton.isMouseOver())
    {
        loadButton.setColour(juce::TextButton::buttonColourId, juce::Colours::royalblue);
    }

    // set the colour of the load button when mouse is not hovering over it 
    else
    {
        loadButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightseagreen);
    }

    // set the colour for the rewind button if mouse over OR it has stopped playing 
    if (rewindButton.isOver() || rewindButton.isMouseOver())
    {
        rewindButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
    }

    // set the colour of the rewind button when mouse is not hovering over it 
    else
    {
        rewindButton.setColour(juce::TextButton::buttonColourId, juce::Colours::cadetblue);
    }

    // set the colour for the fast forward button if mouse over OR it has stopped playing 
    if (fastForwardButton.isOver() || fastForwardButton.isMouseOver())
    {
        fastForwardButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightsteelblue);
    }

    // set the colour of the fast forward button when mouse is not hovering over it 
    else
    {
        fastForwardButton.setColour(juce::TextButton::buttonColourId, juce::Colours::silver);
    }

    // set the colour for the loop button if mouse over OR it has stopped playing 
    if (loopButton.isOver() || loopButton.isMouseOver())
    {
        loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::turquoise);
    }

    // set the colour of the loop button when mouse is not hovering over it 
    else
    {
        loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::teal);
    }
}

void ControlDeck::repaintSliders()
{
    if (volumeSlider.isMouseOver() || positionSlider.isMouseOver() || speedSlider.isMouseOver())
    {
        getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::mistyrose);
    }

    else
    {
        getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::gainsboro);
    }
}

void ControlDeck::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        player->setPosition(0);
        player->playSong();
        paused = false;
    }

    if (button == &stopButton)
    {
        player->stopSong();
        paused = true;
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

        paused = false;
    }

    if (button == &fastForwardButton)
    {
        paused = false;
    }

    if (button == &rewindButton)
    {
        player->rewindSong();
        paused = false;
    }

    // only loop when the loop button has been pressed 
    if (button == &loopButton)
    {
        paused = false;
        player->startLoop(loopButton.getToggleState());
    }

    displayPlayButtonText(paused);
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

void ControlDeck::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

void ControlDeck::displayPlayButtonText(bool pauseButtonStatus)
{
    std::string playButtonText = "";
    switch (pauseButtonStatus)
    {

    case true:
        playButtonText = "Resume";
        break;

    case false:
        playButtonText = "Play";
        break;
    }

    playButton.setButtonText(playButtonText);
}

void ControlDeck::loadDroppedTrack(juce::URL& songURL)
{
    player->loadURL(songURL);
    waveformDisplay.loadURL(songURL);
}