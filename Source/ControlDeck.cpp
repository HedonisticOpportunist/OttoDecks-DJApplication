/*
  ==============================================================================

    ControlDeck.cpp
    Author: anita.pal

    The implementation of the ControlDeck component. 
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
    // load the image buttons 
    // credit goes to: https://icons8.com for all the buttons' images 

    Image rewindImg = ImageCache::getFromMemory(BinaryData::rewind_png, BinaryData::rewind_pngSize); // load the rewind button image 

    rewindButton.setImages
    (false, false, false, rewindImg, 1.0f,
        { Colour(juce::Colours::transparentWhite) }, rewindImg, 1.0f,
        { Colour(Colours::transparentWhite) }, rewindImg,
        1.0f, { Colour(Colours::transparentWhite) });

    Image fastForwardImg = ImageCache::getFromMemory(BinaryData::fastforward_png, BinaryData::fastforward_pngSize); // load the fastforward button image 

    fastForwardButton.setImages
    (false, false, false, fastForwardImg, 1.0f,
        { Colour(juce::Colours::transparentWhite) }, fastForwardImg, 1.0f,
        { Colour(Colours::transparentWhite) }, fastForwardImg,
        1.0f, { Colour(Colours::transparentWhite) });

    Image loopImg = ImageCache::getFromMemory(BinaryData::loop_png, BinaryData::loop_pngSize); // load the loop button image

    loopButton.setImages
    (false, false, false, loopImg, 1.0f,
        { Colour(juce::Colours::transparentWhite) }, loopImg, 1.0f,
        { Colour(Colours::transparentWhite) }, loopImg,
        1.0f, { Colour(Colours::transparentWhite) });

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
    volumeSlider.setSliderStyle(juce::Slider::Rotary);  // make the volume slider rotary 
    positionSlider.setSliderStyle(juce::Slider::Rotary); // make the position slider rotary 
    speedSlider.setSliderStyle(juce::Slider::Rotary); // make the speed slider rotary 

    // set ranges for the slider 
    volumeSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    positionSlider.setRange(0.0, 1.0);

    // adjust the sliders' text box position 
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

    // A call to the buttons and sliders re-painting functions
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

void ControlDeck::repaintSliders()
{
    // if the mouse is over the sliders
    if (volumeSlider.isMouseOver() || positionSlider.isMouseOver() || speedSlider.isMouseOver())
    {
        getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::mistyrose);
    }

    // if the mouse is not in direct vicinity of the sliders 
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
        player->fastForwardSong();
        paused = false;
    }

    if (button == &rewindButton)
    {
        player->rewindSong();
        paused = false;
    }

    // only loop when the loop button has been pressed / is on
    if (button == &loopButton)
    {
        paused = false;
        player->startLoop(loopButton.getToggleState());
    }

    displayPlayButtonText(paused); // this method determines what the play button's text will display 
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

void ControlDeck::repaintButtons()
{
    // set the colour for the play button if mouse over OR it has stopped playing 
    if (playButton.isOver() || playButton.isMouseOver())
    {
        playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkblue);
    }

    // set the colour of the play button when the mouse is not hovering over it 
    else
    {
        playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightslategrey);
    }

    // set the colour of the stop button if mouse is over OR it has stopped playing 
    if (stopButton.isOver() || stopButton.isMouseOver())
    {
        stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::aquamarine);
    }

    // set the colour of the stop button when the mouse is not hovering over it 
    else
    {
        stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::midnightblue);
    }

    // set the colour for the load button if mouse over OR it has stopped playing 
    if (loadButton.isOver() || loadButton.isMouseOver())
    {
        loadButton.setColour(juce::TextButton::buttonColourId, juce::Colours::royalblue);
    }

    // set the colour of the load button when the mouse is not hovering over it 
    else
    {
        loadButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightseagreen);
    }
}

void ControlDeck::displayPlayButtonText(bool pauseButtonStatus)
{
    std::string playButtonText = "";
    switch (pauseButtonStatus)
    {

    case true:
        playButtonText = "Resume"; // if the audio has been paused, showcase 'Resume' 
        break;

    case false:
        playButtonText = "Play"; // if the audio has not been paused, then showcase 'Play' 
        break;
    }

    playButton.setButtonText(playButtonText);
}

void ControlDeck::loadDroppedTrack(juce::URL& songURL)
{
    player->loadURL(songURL);
    waveformDisplay.loadURL(songURL);
}