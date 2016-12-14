#ifndef _SOUNDMANAGER_H
#define _SOUNDMANAGER_H

#include "Trackable.h"
#include <map>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

enum SoundType
{
	CoinSound = 0
};

class SoundManager : public Trackable
{
public:
	SoundManager();
	~SoundManager();

	void playSound(SoundType soundID);
	void addSound(std::string path, SoundType soundID);
private:
	std::map<SoundType, ALLEGRO_SAMPLE*> mSounds;
};

#endif