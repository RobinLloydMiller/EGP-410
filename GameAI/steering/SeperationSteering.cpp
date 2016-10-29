#include "SeperationSteering.h"
#include "Game.h"

SeperationSteering::SeperationSteering(KinematicUnit* pMover)
	: mpMover(pMover)
{
}

//applies velocity is a direction away from a boid that is too close
Steering* SeperationSteering::getSteering()
{
	mLinear = Vector2D();
	int boidCount = 0;

	for (int i = 0; i < gpGame->getKinematicUnitManager()->getUnitCount(); ++i)
	{
		if (gpGame->getKinematicUnitManager()->getUnit(i) != mpMover)
		{
			if (getDistance(gpGame->getKinematicUnitManager()->getUnit(i)->getPosition(), mpMover->getPosition()) < mFlockRadius)
			{
				mLinear += (mpMover->getPosition() - gpGame->getKinematicUnitManager()->getUnit(i)->getPosition());
				++boidCount;
			}
		}
	}

	if (boidCount == 0)
		return this;

	mLinear /= boidCount;
	mLinear.normalize();
	mAngular = 0;

	return this;
}