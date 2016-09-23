#include "AddUnitMessage.h"
#include "Game.h"

AddUnitMessage::AddUnitMessage(SteeringType sType, float xOffset, float orientation, Vector2D& velocity, float rotationVel, float maxVelocity, float maxAcceleration)
:GameMessage(ADD_UNIT_MESSAGE)
,mSteeringType(sType)
,mXOffset(xOffset)
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
	Vector2D pos(gpGame->getPlayer()->getPosition().getX() + mXOffset, gpGame->getPlayer()->getPosition().getY());
	//add unit
	gpGame->getKinematicUnitManager()->addUnit(gpGame->getEnemySprite(), pos, mOrientation, mVelocity, mRotationVel, mMaxVelocity, mMaxAcceleration);

	//set steering type based on parameter
	if(mSteeringType == 0)
		gpGame->getKinematicUnitManager()->getUnit(gpGame->getKinematicUnitManager()->getUnitCount() - 1)->dynamicArrive(gpGame->getKinematicUnitManager()->getPlayer());
	else if(mSteeringType == 1)
		gpGame->getKinematicUnitManager()->getUnit(gpGame->getKinematicUnitManager()->getUnitCount() - 1)->dynamicSeek(gpGame->getKinematicUnitManager()->getPlayer());
}