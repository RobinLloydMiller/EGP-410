#include "SeperationSteering.h"
#include "Game.h"

SeperationSteering::SeperationSteering(KinematicUnit* pMover)
	: mpMover(pMover)
{
}

Steering* SeperationSteering::getSteering()
{
	for (int i = 0; i < gpGame->getKinematicUnitManager()->getUnitCount(); ++i)
	{
		if (gpGame->getKinematicUnitManager()->getUnit(i) != mpMover)
		{
			if (getDistance(gpGame->getKinematicUnitManager()->getUnit(i)->getPosition(), mpMover->getPosition()) < mFlockRadius)
			{
				mLinear += (mpMover->getPosition() - gpGame->getKinematicUnitManager()->getUnit(i)->getPosition());
				++mBoidCount;
			}
		}
	}

	if (mBoidCount == 0)
		return this;

	mLinear /= mBoidCount;
	mLinear.normalize();
	mAngular = 0;

	return this;
}