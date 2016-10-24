#include "AlignmentSteering.h"
#include "Game.h"

AlignmentSteering::AlignmentSteering(KinematicUnit* pMover)
: mpMover(pMover)
{
}

Steering* AlignmentSteering::getSteering()
{
	for (int i = 0; i < gpGame->getKinematicUnitManager()->getUnitCount(); ++i)
	{
		if (gpGame->getKinematicUnitManager()->getUnit(i) != mpMover)
		{
			if (getDistance(gpGame->getKinematicUnitManager()->getUnit(i)->getPosition(), mpMover->getPosition()) < mFlockRadius)
			{
				mLinear += gpGame->getKinematicUnitManager()->getUnit(i)->getVelocity();
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