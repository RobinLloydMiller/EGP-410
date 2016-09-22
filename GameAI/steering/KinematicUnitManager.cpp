#include "KinematicUnitManager.h"

KinematicUnitManager::~KinematicUnitManager()
{
	delete mpPlayer;
	mpPlayer = NULL;

	for (size_t i = 0; i < mUnits.size(); i++)
	{
		delete mUnits[i];
		mUnits[i] = NULL;
	}

	mUnits.clear();
}

void KinematicUnitManager::update(float time)
{
	for(auto it : mUnits)
	{
		it->update(time);
	}

	mpPlayer->update(time);

	return;
}

void KinematicUnitManager::draw(GraphicsBuffer* pBuffer)
{
	for (auto it : mUnits)
	{
		it->draw(pBuffer);
	}

	mpPlayer->draw(pBuffer);

	return;
}

bool KinematicUnitManager::addUnit(Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity, float maxAcceleration)
{
	if (pSprite == NULL)
	{
		std::cout << "Couldn't create Kinematic Unit, Sprite is null\n";
		return false;
	}

	mUnits.push_back(new KinematicUnit(pSprite, position, orientation, velocity, rotationVel, maxVelocity, maxAcceleration));

	return true;
}

bool KinematicUnitManager::deleteUnit(size_t index)
{
	if (mUnits.size() <= index || mUnits[index] == NULL)
		return false;

	mUnits.erase(mUnits.begin() + index);

	return true;
}

bool KinematicUnitManager::deleteUnit()
{
	int index = rand() % mUnits.size();

	return deleteUnit(index);
}

bool KinematicUnitManager::addPlayer(Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity, float maxAcceleration)
{
	if (pSprite == NULL)
	{
		std::cout << "Couldn't create Kinematic Unit, Sprite is null\n";
		return false;
	}

	mpPlayer = new KinematicUnit(pSprite, position, orientation, velocity, rotationVel, maxVelocity, maxAcceleration);

	return true;
}