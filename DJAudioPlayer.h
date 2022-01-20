#pragma once
// assumes your JuceHeader file is here
// check your MainComponent.h to see
// how the include is configured on your
// system
#include "../JuceLibraryCode/JuceHeader.h"
class DJAudioPlayer : public AudioSource
{
public:
	/** The DJAudioPlayer constructor */
	DJAudioPlayer();
	/** The DJAudioPlayer destructor */
	~DJAudioPlayer();
	/**loads a file from a given URL  */
	void loadURL(URL file);
	/** Plays a file */
	void play();
	/** Stops playing a file */
	void stop();
	/** Sets a position */
	void setPosition(double posInSecs);
	/** Sets a gain */
	void setGain(double gain);
	/** Prepares to play a file */
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	/** Gets the next audio block  */
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
	/** Releases resources */
	void releaseResources() override;
	/** Sets a relative position */
	void setPositionRelative(double pos);


private:
	AudioFormatManager formatManager;
	std::unique_ptr<AudioFormatReaderSource> readerSource;
	AudioTransportSource transportSource;
};
