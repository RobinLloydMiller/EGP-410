#include "CohesionSteering.h"
#include "Game.h"

CohesionSteering::CohesionSteering(KinematicUnit* pMover)
	: mpMover(pMover)
{
}

//applies velocity in average direction of other boid
Steering* CohesionSteering::getSteering()
{
	mLinear = Vector2D();
	int boidCount = 0;
	
	for (int i = 0; i < gpGame->getKinematicUnitManager()->getUnitCount(); ++i)
	{
		if (gpGame->getKinematicUnitManager()->getUnit(i) != mpMover)
		{
			if (getDistance(gpGame->getKinematicUnitManager()->getUnit(i)->getPosition(), mpMover->getPosition()) < mFlockRadius)
			{
				mLinear += gpGame->getKinematicUnitManager()->getUnit(i)->getPosition();
				++boidCount;
			}
		}
	}

	if (boidCount == 0)
		return this;

	mLinear /= boidCount;
	mLinear -= mpMover->getPosition();
	mLinear.normalize();
	mAngular = 0;

	return this;
}