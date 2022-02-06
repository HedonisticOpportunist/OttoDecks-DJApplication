
/*
  ==============================================================================

	DJAudioPlayer.h
	Author:  @anita.pal

	This class deals with the audio and the way various ways it playback 
	can be controlled / manipulated. 
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

	/** Loads a file from a given URL */
	void loadURL(URL& file);

	/** Plays a file */
	void playSong();

	/** Stops playing a file */
	void stopSong();

	/** Rewinds a song **/
	void rewindSong();

	/** Fast forwards a song */
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

	/** Gets the relative position of the play head */
	double getPositionRelative();

	/** Starts a loop */
	void startLoop();

	/** Ends a loop */
	void endLoop();

	/** Returns the file length in seconds */
	double getFileLengthSeconds();

	/** Override methods from the PositionableAudioSource class */
	void setNextReadPosition(juce::int64 newPosition) override;
	juce::int64 getNextReadPosition() const override;
	juce::int64 getTotalLength() const override;
	bool isLooping() const override;

private:

	// Private members of the class 
	AudioFormatManager& formatManager;
	std::unique_ptr<AudioFormatReaderSource> readerSource;
	AudioTransportSource transportSource;
	ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
};
