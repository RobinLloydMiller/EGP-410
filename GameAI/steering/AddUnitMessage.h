#ifndef _ADDUNITMESSAGE_H
#define _ADDUNITMESSAGE_H

#include "GameMessage.h"
#include "Vector2D.h"

enum SteeringType
{
	DYNAMIC_ARRIVE,
	DYNAMIC_SEEK,
	WANDER_AND_SEEK,
	WANDER_AND_FLEE,
	BOIDS
};

class AddUnitMessage : public GameMessage
{
public:
	AddUnitMessage(SteeringType sType, float xOffset, float orientation, Vector2D& velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f);
	~AddUnitMessage();
	
	void process();

private:
	float mOrientation, mRotationVel, mMaxVelocity, mMaxAcceleration, mXOffset;
	Vector2D mVelocity;
	SteeringType mSteeringType;
};

#endif