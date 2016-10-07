#include "WanderAndSeekSteering.h"
#include "Game.h"

WanderAndSeekSteering::WanderAndSeekSteering(KinematicUnit * pMover, KinematicUnit * pTarget, bool shouldFlee)
:mpMover(pMover), mpTarget(pTarget), mShouldFlee(shouldFlee)
{
	newWanderTarget();
}

Steering* WanderAndSeekSteering::getSteering()
{
	float distance = getDistance(mpMover->getPosition(), mpTarget->getPosition());
	//std::cout << distance << std::endl;

	//seek
	if (distance < mSeekRadius)
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
	//new wander behavior that interacts with walls better
	//wanders to random point until close to it than chooses a new point
	//wander
	else if(getDistance(mpMover->getPosition(), mWanderTarget) > mWanderTargetRadius)
	{
		mLinear = mWanderTarget - mpMover->getPosition();
		mLinear.normalize();
		mLinear *= mpMover->getMaxVelocity();
		mAngular = 0;

		//mApplyDirectly = true;
		//mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
		//mAngular = mpMover->getOrientation() * (genRandomBinomial() * MAX_WANDER_ROTATION);
	}
	else if (getDistance(mpMover->getPosition(), mWanderTarget) < mWanderTargetRadius)
	{
		newWanderTarget();
	}

	//avoid other units
	int closestIndex = -1;
	int closestDistance = mAvoidRadius;

	for (int j = 0; j < gpGame->getKinematicUnitManager()->getUnitCount(); j++)
	{
		if (gpGame->getKinematicUnitManager()->getUnit(j) != mpMover)
		{
			float dist = getDistance(gpGame->getKinematicUnitManager()->getUnit(j)->getPosition(), mpMover->getPosition());

			if (dist < closestDistance)
			{
				closestDistance = dist;
				closestIndex = j;
			}
		}
	}

	if (closestIndex != -1)
	{
		mApplyDirectly = false;
		//float x = (mpMover->getVelocity().getX() + gpGame->getKinematicUnitManager()->getUnit(closestIndex)->getVelocity().getX()) / 2.0f;
		//float y = (mpMover->getVelocity().getY() + gpGame->getKinematicUnitManager()->getUnit(closestIndex)->getVelocity().getY()) / 2.0f;
		//Vector2D direction(x, y);
		Vector2D direction = mpMover->getPosition() - gpGame->getKinematicUnitManager()->getUnit(closestIndex)->getPosition();
		direction.normalize();
		direction *= mpMover->getMaxVelocity();
		mLinear = direction;
		mAngular = 0;
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