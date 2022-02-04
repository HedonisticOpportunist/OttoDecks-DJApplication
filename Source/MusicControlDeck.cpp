/*
  ==============================================================================

    MusicLibraryControlDeck.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MusicControlDeck.h"

MusicLibraryControlDeck::MusicLibraryControlDeck
(
    ControlDeck* _controlDeckOne,
    ControlDeck* _controlDeckTwo):
    controlDeckOne(_controlDeckOne), 
    controlDeckTwo(_controlDeckTwo)
{
    // background image 
    // @credit https://unsplash.com/@gradienta
    backgroundImage = ImageCache::getFromMemory(BinaryData::background_img_png, BinaryData::background_img_pngSize);

    // make buttons visible 
    addAndMakeVisible(loopButton);
    addAndMakeVisible(rewindButton);
    addAndMakeVisible(fastForwardButton);

    // add listeners to the buttons 
    loopButton.addListener(this);
    rewindButton.addListener(this);
    fastForwardButton.addListener(this);
  
}

MusicLibraryControlDeck::~MusicLibraryControlDeck()
{
}

// R4C: GUI layout includes the music library component from R3
void MusicLibraryControlDeck::paint (juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::whitesmoke);
    graphics.drawImage(backgroundImage, getLocalBounds().toFloat());

    //A call to the buttons and sliders painting functions
    repaintButtons();
}

void MusicLibraryControlDeck::resized()
{
    double rowH = getHeight() / 3.0;

    // play, stop and load button positions
    loopButton.setBounds(0, 0, getWidth() / 2, rowH * 1.0);
    rewindButton.setBounds(0, rowH * 1.0, getWidth() / 2, rowH * 1.0);
    fastForwardButton.setBounds(0, rowH * 2.0, getWidth() / 2, rowH * 1.0);
}

void MusicLibraryControlDeck::repaintButtons()
{
    // set the colour for the load to deck one button if mouse over OR it has stopped playing 
    if (loopButton.isOver() || loopButton.isMouseOver())
    {
        loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::mistyrose);
    }

    // set the colour of the load to deck one button when mouse is not hovering over it 
    else
    {
        loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::olive);
    }

    // set the colour for the load to deck two button if mouse over OR it has stopped playing 
    if (rewindButton.isOver() || rewindButton.isMouseOver())
    {
        rewindButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightcoral);
    }

    // set the colour of the load to deck two button when mouse is not hovering over it 
    else
    {
        rewindButton.setColour(juce::TextButton::buttonColourId, juce::Colours::gainsboro);
    }

    // set the colour for the load button if mouse over OR it has stopped playing 
    if (fastForwardButton.isOver() || fastForwardButton.isMouseOver())
    {
        fastForwardButton.setColour(juce::TextButton::buttonColourId, juce::Colours::cornsilk);
    }

    // set the colour of the load button when mouse is not hovering over it 
    else
    {
        fastForwardButton.setColour(juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
    }
}

void MusicLibraryControlDeck::buttonClicked(Button* button)
{
    bool paused = false;

    if (button == &fastForwardButton)
    {
        paused = false;
    }

    if (button == &rewindButton)
    {
        //player->rewindSong();
        paused = false;
    }

    // only loop when the loop button has been pressed 
    if (button == &loopButton)
    {
        paused = false;
        //player->startLoop();
    }
    else
    {
        //player->endLoop();
    }
}