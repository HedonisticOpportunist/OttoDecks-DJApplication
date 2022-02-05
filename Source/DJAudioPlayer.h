
/*
  ==============================================================================

	DJAudioPlayer.h
	Author:  anita.pal

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer : public AudioSource,
	                  public PositionableAudioSource
{
public:

	/** The DJAudioPlayer constructor */
	DJAudioPlayer(AudioFormatManager& formatManager);

	/** The DJAudioPlayer destructor */
	~DJAudioPlayer() override;

	/**loads a file from a given URL  */
	void loadURL(URL file);

	/** Plays a file */
	void playSong();

	/** Stops playing a file */
	void stopSong();

	/** Rewinds a file **/
	void rewindSong();

	/** Fastforwards a file */
	void fastForwardSong();

	/** Sets a position */
	void setPosition(double posInSecs);

	/** Sets a gain */
	void setGain(double gain);

	/** Prepares to play a file */
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

	/** Gets the next audio block */
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;

	/** Releases resources */
	void releaseResources() override;

	/** Sets a relative position */
	void setPositionRelative(double pos);

	/** Sets a speed */
	void setSpeed(double speed);

	/** Get the relative position of the play head */
	double getPositionRelative();

	/** Starts a loop */
	void startLoop();

	/** Ends a loop */
	void endLoop();

	double determineFileLengthInSeconds();

	/** Override methods from the PositionableAudioSource class */
	void setNextReadPosition(juce::int64 newPosition) override;
	juce::int64 getNextReadPosition() const override;
	juce::int64 getTotalLength() const override;
	bool isLooping() const override;

private:

	// private members of the class 
	AudioFormatManager& formatManager;
	std::unique_ptr<AudioFormatReaderSource> readerSource;
	AudioTransportSource transportSource;
	ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
};
