#include "AddUnitMessage.h"
#include "Game.h"

AddUnitMessage::AddUnitMessage(SteeringType sType, Vector2D pos, float orientation, Vector2D& velocity, float rotationVel, float maxVelocity, float maxAcceleration)
:GameMessage(ADD_UNIT_MESSAGE)
,mSteeringType(sType)
,mPos(pos)
,mOrientation(orientation)
,mVelocity(velocity)
,mRotationVel(rotationVel)
,mMaxVelocity(maxVelocity)
,mMaxAcceleration(maxAcceleration)
{
}

AddUnitMessage::~AddUnitMessage()
{
}

void AddUnitMessage::process()
{
	//add unit
	gpGame->getKinematicUnitManager()->addUnit(gpGame->getEnemySprite(), mPos, mOrientation, mVelocity, mRotationVel, mMaxVelocity, mMaxAcceleration);

	//set steering type based on parameter
	if (mSteeringType == DYNAMIC_ARRIVE)
		gpGame->getKinematicUnitManager()->getUnit(gpGame->getKinematicUnitManager()->getUnitCount() - 1)->dynamicArrive(gpGame->getPlayer());
	else if (mSteeringType == DYNAMIC_SEEK)
		gpGame->getKinematicUnitManager()->getUnit(gpGame->getKinematicUnitManager()->getUnitCount() - 1)->dynamicSeek(gpGame->getPlayer());
	else if (mSteeringType == WANDER_AND_SEEK)
		gpGame->getKinematicUnitManager()->getUnit(gpGame->getKinematicUnitManager()->getUnitCount() - 1)->wanderAndSeek(gpGame->getPlayer());
	else if (mSteeringType == WANDER_AND_FLEE)
		gpGame->getKinematicUnitManager()->getUnit(gpGame->getKinematicUnitManager()->getUnitCount() - 1)->wanderAndSeek(gpGame->getPlayer(), true);
	else if (mSteeringType == BOIDS)
		gpGame->getKinematicUnitManager()->getUnit(gpGame->getKinematicUnitManager()->getUnitCount() - 1)->boids();
}