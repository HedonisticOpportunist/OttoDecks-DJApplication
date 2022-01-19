#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    addAndMakeVisible(playButton);
    playButton.addListener(this);

    addAndMakeVisible(stopButton);
    stopButton.addListener(this);

    addAndMakeVisible(volumeSlider);
    volumeSlider.setRange(0, 1);

    addAndMakeVisible(loadButton);
    loadButton.addListener(this);
    loadButton.setButtonText("LOAD");

    formatManager.registerBasicFormats();

}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    playing = false;

    gain = 0.5;
    phase = 0;
    dphase = 0;

    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)

    if (!playing)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    /*

    auto* leftChannel = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto* rightChannel = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);

    for (auto i = 0;i < bufferToFill.numSamples; ++i)
    {
        auto sample = fmod(phase, 1.0f);
        phase += fmod(dphase, 0.01f);
        dphase += 0.0000005f;

        leftChannel[i] = sample * 0.125f * gain;
        rightChannel[i] = sample * 0.125f * gain;
    } */

    transportSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    transportSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    playButton.setBounds(0, 0, getWidth(), getHeight() / 5);
    stopButton.setBounds(0, getHeight() / 5, getWidth(), getHeight() / 5);
    loadButton.setBounds(0, getHeight() / 5 * 2, getWidth(), getHeight() / 5);
    volumeSlider.setBounds(0, getHeight() / 5 * 3, getWidth(), getHeight() / 5);
}

void MainComponent::buttonClicked(Button* button)
{
    DBG(" MainComponent::buttonClicked: They clicked a button");
    if (button == &playButton) // clicked button has same memory address as playButton
    {
        playing = true;
        dphase = 0;

        transportSource.setPosition(0);
        transportSource.start();
    }
    if (button == &stopButton)
    {
        playing = false;;
        transportSource.stop();
    }

    if (button == &loadButton)
    {
        auto dlgFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;
        this->chooser.launchAsync(dlgFlags, [this](const juce::FileChooser& chooser)
            {
                auto fileUri = chooser.getURLResult();
                this->loadURL(fileUri);
            });
    }
}

void MainComponent::sliderValueChanged(Slider* slider)
{
    if (slider == &volumeSlider)
    {
        DBG("MainComponent::sliderValueChanged: gainSlider");
        gain = (float) volumeSlider.getValue();

        transportSource.setGain(gain);
    }
}

void MainComponent::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<AudioFormatReaderSource> newSource
        (new AudioFormatReaderSource(reader, true));
        transportSource.setSource(
            newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}