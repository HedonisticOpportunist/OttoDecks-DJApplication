/*
  ==============================================================================

    MainDJAudioManager.cpp
    Author:  anita.pal

  ==============================================================================
*/

#include "MainDJAudioManager.h"

MainDJAudioManager::MainDJAudioManager()
{
    setSize(1200, 800);

    // add background image 
    // https://c4.wallpaperflare.com/wallpaper/548/896/920/cat-headphones-lilac-funny-wallpaper-preview.jpg
    backgroundImage = ImageCache::getFromMemory(BinaryData::cat_background_png, BinaryData::cat_background_pngSize);

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

    // make the music control decks visible
    addAndMakeVisible(musicControlDeck);

    // make the search field visible 
    addAndMakeVisible(searchField);

    // make the playlist component visible 
    addAndMakeVisible(playListComponent);
}

MainDJAudioManager::~MainDJAudioManager()
{
    shutdownAudio();
}

// R1B: can play two or more tracks
void MainDJAudioManager::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    mixerSource.addInputSource(&deckOnePlayer, false);
    mixerSource.addInputSource(&deckTwoPlayer, false);

    deckOnePlayer.prepareToPlay(samplesPerBlockExpected, sampleRate);
    deckTwoPlayer.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainDJAudioManager::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainDJAudioManager::releaseResources()
{
    mixerSource.removeAllInputs();
    mixerSource.releaseResources();

    deckOnePlayer.releaseResources();
    deckTwoPlayer.releaseResources();
}

void MainDJAudioManager::paint (juce::Graphics& graphics)
{
    graphics.drawImage(backgroundImage, getLocalBounds().toFloat());
}

void MainDJAudioManager::resized()
{
    /**
    *  DECK 1 | DECK 2 
    | MUSIC CONTROL DECK | PLAYLIST |
    | SEARCH FIELD
    **/

    // DECKS
    deck1.setBounds(0, 0, getWidth() / 4.2, getHeight() / 4.2);
    deck2.setBounds(getWidth() / 4.2, 0, getWidth() / 4.2, getHeight() / 4.2);

    // MUSIC CONTROL DECK 
    musicControlDeck.setBounds(0, getHeight() / 4.2, getWidth() / 4.2, getHeight() / 4.2);

    // PLAYLIST
    playListComponent.setBounds(getWidth() / 4.2, getHeight() / 4.2, getWidth() / 4.2, getHeight() / 4.2);

    // SEARCH FIELD 
    searchField.setBounds(0, getHeight() - 420, getWidth() / 4.2, getHeight() / 4.2);
}