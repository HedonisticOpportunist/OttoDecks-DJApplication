/*
  ==============================================================================

	DJAudioPlayer.cpp
	Author: @anita.pal

	The implementation of the DJAudioPlayer class. 
  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager)
	: formatManager(_formatManager)
{
	formatManager.registerBasicFormats();
}
DJAudioPlayer::~DJAudioPlayer()
{
}

void DJAudioPlayer::loadURL(URL& audioURL)
{
	auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));

	if (reader != nullptr) // if the reader is not a null pointer 
	{
		std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
		transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
		readerSource.reset(newSource.release());
	}
}

void DJAudioPlayer::playSong()
{
	transportSource.start();
}

void DJAudioPlayer::stopSong()
{
	// @ credit Matthias Truxa (UoL Slack Channel post) 
	juce::Thread::launch([&]() 
		{
			this->transportSource.stop();
		});
}

void DJAudioPlayer::rewindSong()
{
	int currentPosition = transportSource.getCurrentPosition(); // get the current position of the audio 

	if (currentPosition > 0.5)
	{
		setPosition(currentPosition - 5.0); // subtract a value of 5 from the current position 
	}

	else
	{
		setPosition(0.0); // reset the position to a value of 0
	}
}

void DJAudioPlayer::fastForwardSong()
{
	double lastPositionHeld = transportSource.getLengthInSeconds(); // get the length in seconds, showcasing what the last file length was
	int currentPosition = transportSource.getCurrentPosition(); // get the current position  of the audio 

	if (currentPosition + 1.5 != lastPositionHeld && currentPosition + 1.5 > lastPositionHeld)
	{
		transportSource.setPosition(currentPosition + 2.0); // add a value of 2 to the current position 
	}
}

void DJAudioPlayer::setPosition(double posInSecs)
{
	if (posInSecs < 0 || posInSecs > transportSource.getLengthInSeconds()) 
	{
		return;
	}

	transportSource.setPosition(posInSecs); // set the position to the seconds passed into the argument 
}

void DJAudioPlayer::setGain(double gain)
{
	transportSource.setGain(gain);
}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
	resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
	resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources()
{
	transportSource.releaseResources();
	resampleSource.releaseResources();
}

void DJAudioPlayer::setPositionRelative(double pos)
{
	double posInSecs = pos * transportSource.getLengthInSeconds();
	setPosition(posInSecs);
}

void DJAudioPlayer::setSpeed(double ratio)
{
	if (ratio < 0 || ratio > 100.0)
	{
		return;
	}

	else 
	{
		resampleSource.setResamplingRatio(ratio);
	}
}

double DJAudioPlayer::getPositionRelative()
{
	return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

void DJAudioPlayer::startLoop(bool buttonIsOn)
{
	if (readerSource != nullptr) // if the reader source is not a null pointer 
	{
		readerSource->setLooping(buttonIsOn); // start looping 
	}
}

double DJAudioPlayer::getFileLengthSeconds()
{
	return transportSource.getLengthInSeconds(); // get the file length in seconds from the transport source 
}