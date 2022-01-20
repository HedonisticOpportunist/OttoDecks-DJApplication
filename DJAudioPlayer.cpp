#include "DJAudioPlayer.h"
DJAudioPlayer::DJAudioPlayer()
{
	formatManager.registerBasicFormats();
}
DJAudioPlayer::~DJAudioPlayer()
{
}
void DJAudioPlayer::loadURL(URL audioURL)
{
	auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
	if (reader != nullptr) // good file!
	{
		std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader,
			true));
		transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
		readerSource.reset(newSource.release());
	}
}
void DJAudioPlayer::play()
{
	transportSource.start();
}

void DJAudioPlayer::stop()
{
	transportSource.stop();
}

void DJAudioPlayer::setPosition(double posInSecs)
{
	if (posInSecs < 0 || posInSecs > transportSource.getLengthInSeconds()) {
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
}

void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
	if (readerSource.get() == nullptr)

	{
		bufferToFill.clearActiveBufferRegion();
		return;
	}

	transportSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources()
{
	transportSource.releaseResources();
}

void DJAudioPlayer::setPositionRelative(double pos)
{
	double posInSecs = pos * transportSource.getLengthInSeconds();
	setPosition(posInSecs);
}
