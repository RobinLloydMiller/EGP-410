#include "CohesionSteering.h"
#include "Game.h"

CohesionSteering::CohesionSteering(KinematicUnit* pMover)
	: mpMover(pMover)
{
}

Steering* CohesionSteering::getSteering()
{
	for (int i = 0; i < gpGame->getKinematicUnitManager()->getUnitCount(); ++i)
	{
		if (gpGame->getKinematicUnitManager()->getUnit(i) != mpMover)
		{
			if (getDistance(gpGame->getKinematicUnitManager()->getUnit(i)->getPosition(), mpMover->getPosition()) < mFlockRadius)
			{
				mLinear += gpGame->getKinematicUnitManager()->getUnit(i)->getPosition();
				++mBoidCount;
			}
		}
	}

	if (mBoidCount == 0)
		return this;

	mLinear /= mBoidCount;
	mLinear -= mpMover->getPosition();
	mLinear.normalize();
	mAngular = 0;

	return this;
}