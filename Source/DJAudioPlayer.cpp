/*
  ==============================================================================

	DJAudioPlayer.cpp
	Author:  anita.pal

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

// R1A: can load audio files into audio players
void DJAudioPlayer::loadURL(URL audioURL)
{
	auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));

	if (reader != nullptr) 
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
	transportSource.stop();
}

void DJAudioPlayer::rewindSong()
{
	int currentPosition = transportSource.getCurrentPosition();

	if (currentPosition > 0.5)
	{
		setPosition(currentPosition - 5.0);
	}

	else
	{
		setPosition(0.0);
	}
}

void DJAudioPlayer::fastForwardSong()
{
	double lastPositionHeld = transportSource.getLengthInSeconds();
	int currentPosition = transportSource.getCurrentPosition();

	if (currentPosition + 1.5 != lastPositionHeld && currentPosition + 1.5 > lastPositionHeld)
	{
		transportSource.setPosition(currentPosition + 2.0);
	}
}

void DJAudioPlayer::setPosition(double posInSecs)
{
	if (posInSecs < 0 || posInSecs > transportSource.getLengthInSeconds()) 
	{
		DBG("DJAudioPlayer::setPosition: warning set position " << posInSecs \
			<< " greater than length " << transportSource.getLengthInSeconds());
		return;
	}

	transportSource.setPosition(posInSecs);
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
		std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
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

void DJAudioPlayer::setNextReadPosition(juce::int64 newPosition)
{

}

juce::int64 DJAudioPlayer::getNextReadPosition() const
{
	return readerSource->getNextReadPosition();
}

juce::int64 DJAudioPlayer::getTotalLength() const
{
	return readerSource->getTotalLength();
}

bool DJAudioPlayer::isLooping() const
{
	return false;
}

void DJAudioPlayer::startLoop()
{
	
	if (readerSource != nullptr)
	{
		readerSource->setLooping(true);
	}
}

void DJAudioPlayer::endLoop()
{
	if (readerSource != nullptr)
	{
		readerSource->setLooping(false);
	}
}

double DJAudioPlayer::getLengthInSeconds()
{
	return transportSource.getLengthInSeconds();
}