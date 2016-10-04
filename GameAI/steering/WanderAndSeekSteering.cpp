#include "WanderAndSeekSteering.h"
#include "Game.h"

WanderAndSeekSteering::WanderAndSeekSteering(KinematicUnit * pMover, KinematicUnit * pTarget, bool shouldFlee)
:mpMover(pMover), mpTarget(pTarget), mShouldFlee(shouldFlee)
{
}

Steering* WanderAndSeekSteering::getSteering()
{
	float distance = getDistance(mpMover->getPosition(), mpTarget->getPosition());
	std::cout << distance << std::endl;

	//seek
	if (distance < SEEK_RADIUS)
	{
		mApplyDirectly = false;

		if (!mShouldFlee)
			mLinear = mpTarget->getPosition() - mpMover->getPosition();
		else
			mLinear = mpMover->getPosition() - mpTarget->getPosition();

		mLinear.normalize();
		mLinear *= mpMover->getMaxVelocity();
		mAngular = 0;
	}
	//wander
	else
	{
		mApplyDirectly = true;
		mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
		mAngular = mpMover->getOrientation() * (genRandomBinomial() * MAX_WANDER_ROTATION);
	}

	return this;
}

//distance formula for 2D vector
float WanderAndSeekSteering::getDistance(Vector2D pos, Vector2D pos2)
{
	float x = pos2.getX() - pos.getX();
	float y = pos2.getY() - pos.getY();

	x *= x;
	y *= y;

	return pow((x + y), .5f);
}