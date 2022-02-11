/*
  ==============================================================================

    WaveformDisplay.cpp
    Author:  anita.pal

    The implementation of the WaveFormDisplay component. 
  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(
    AudioFormatManager& formatManagerToUse,
    AudioThumbnailCache& cacheToUse)
    : audioThumbnail(1000, formatManagerToUse, cacheToUse), fileLoaded(false), position(0)
{
    audioThumbnail.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::midnightblue);
    graphics.setColour(juce::Colours::mediumpurple);
    graphics.drawRect(getLocalBounds(), 1);

    if (fileLoaded)
    {
        // setting the colour of the waveform 
        graphics.setColour(juce::Colours::blueviolet); 
        audioThumbnail.drawChannel(graphics, getLocalBounds(), 0, audioThumbnail.getTotalLength(), 0, 1.0f);
        graphics.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());
    }
    else
    {
        graphics.setFont(15.0f);
        graphics.drawText("File has not been loaded...", getLocalBounds(),
            Justification::centred, true);
    }
}

void WaveformDisplay::resized()
{
}

void WaveformDisplay::loadURL(URL audioURL)
{
    audioThumbnail.clear();
    fileLoaded = audioThumbnail.setSource(new URLInputSource(audioURL));
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source)
{
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position && !isnan(position))
    {
        position = pos;
        repaint();
    }
}