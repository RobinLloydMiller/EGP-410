#include "SoundManager.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	for (auto &it : mSounds)
		al_destroy_sample(it.second);

	mSounds.clear();
}

void SoundManager::playSound(SoundType soundID)
{
	if (!mSounds[soundID])
		return;

	al_play_sample(mSounds[soundID], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void SoundManager::addSound(std::string path, SoundType soundID)
{
	ALLEGRO_SAMPLE* sample = NULL;
	sample = al_load_sample(path.c_str());

	if (!sample)
	{
		std::cout << "failed to load sound at " << path.c_str() << std::endl;
		return;
	}

	mSounds[soundID] = sample;
}
