/*
  ==============================================================================

    MainComponent.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize(800, 600);

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
    addAndMakeVisible(playlistComponent);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

// R1B: can play two or more tracks
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);

    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    mixerSource.removeAllInputs();
    mixerSource.releaseResources();

    player1.releaseResources();
    player2.releaseResources();
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    deck1.setBounds(0, 0, getWidth() / 2, getHeight() / 2);
    deck2.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight() / 2);
    playlistComponent.setBounds(0, getHeight() / 2, getWidth(), getHeight() / 2);

}