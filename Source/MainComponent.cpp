/*
  ==============================================================================

    MainComponent.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize(1200, 800);

    // add background image 
    // credit @ https://unsplash.com/@markusspiske
    backgroundImage = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);

    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
        && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
            [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    }

    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(2, 2);
    }

    // make the decks visible 
    addAndMakeVisible(deck1);
    addAndMakeVisible(deck2);

    // make the music library-related decks visible 
    addAndMakeVisible(musicControlDeck);
    addAndMakeVisible(playlistComponent);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

// R1B: can play two or more tracks
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    mixerSource.addInputSource(&deckOnePlayer, false);
    mixerSource.addInputSource(&deckTwoPlayer, false);

    deckOnePlayer.prepareToPlay(samplesPerBlockExpected, sampleRate);
    deckTwoPlayer.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    mixerSource.removeAllInputs();
    mixerSource.releaseResources();

    deckOnePlayer.releaseResources();
    deckTwoPlayer.releaseResources();
}

void MainComponent::paint (juce::Graphics& graphics)
{
    graphics.drawImage(backgroundImage, getLocalBounds().toFloat());
}

void MainComponent::resized()
{
    // layout is smaller, as we want to display the background image 
    deck1.setBounds(0, 0, getWidth() / 3.2, getHeight() / 3.2);
    deck2.setBounds(getWidth() / 3.2, 0, getWidth() / 3.2, getHeight() / 3.2); 
    musicControlDeck.setBounds(getWidth() / 3.2, 0, getWidth() / 3.2, getHeight() / 3.2);
    playlistComponent.setBounds(0, getHeight() / 3, getWidth() / 3, getHeight() / 3);
}