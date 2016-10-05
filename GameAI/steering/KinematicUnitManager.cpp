#include "KinematicUnitManager.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "ExitGameMessage.h"

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
	if ((mUnits.size() <= index && index >= 0) || mUnits[index] == NULL)
		return false;

	delete mUnits[index];
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

void KinematicUnitManager::updateMaxVelocity(float vel)
{
	for (auto it : mUnits)
	{
		it->setMaxVelocity(vel);
	}
	return;
}

void KinematicUnitManager::updateMaxAcceleration(float accel)
{
	for (auto it : mUnits)
	{
		it->setMaxAcceleration(accel);
	}
	return;
}

void KinematicUnitManager::updateReactionRadius(float radius)
{
	for (auto it : mUnits)
	{
		it->getSteering()->setRadius(radius);
	}
	return;
}

void KinematicUnitManager::updateAngularVelocity(float angVel)
{
	for (auto it : mUnits)
	{
		it->getSteering()->setAngular(angVel);
	}
	return;
}
