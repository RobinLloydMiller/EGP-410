#include "BoidsSteering.h"
#include "AlignmentSteering.h"
#include "CohesionSteering.h"
#include "SeperationSteering.h"
#include "KinematicUnit.h"
#include "KinematicUnitManager.h"
#include "Game.h"

BoidsSteering::BoidsSteering(KinematicUnit* pMover)
:mpMover(pMover)
{
	mpAlignmentSteering = new AlignmentSteering(pMover);
	mpCohesionSteering = new CohesionSteering(pMover);
	mpSeperationSteering = new SeperationSteering(pMover);

	//newWanderTarget();
}

BoidsSteering::~BoidsSteering()
{
	delete mpAlignmentSteering;
	delete mpCohesionSteering;
	delete mpSeperationSteering;
}

Steering* BoidsSteering::getSteering()
{
	mApplyDirectly = false;
	mLinear = Vector2D(0.1f, 0.1f);

	/*bool free = true;
	for (int i = 0; i < gpGame->getKinematicUnitManager()->getUnitCount(); ++i)
	{
		if (gpGame->getKinematicUnitManager()->getUnit(i) != mpMover)
		{
			if (getDistance(gpGame->getKinematicUnitManager()->getUnit(i)->getPosition(), mpMover->getPosition()) < 200)
			{
				free = false; //sets false if any close
			}
		}
	}
	if (free) // only does wander if not found in a boid group
	{
		if (getDistance(mpMover->getPosition(), mWanderTarget) > mWanderTargetRadius)
		{
			mLinear = mWanderTarget - mpMover->getPosition();
			mLinear *= mpMover->getMaxVelocity();
			mLinear.normalize();
		}
		else
		{
			newWanderTarget();
		}
	}*/


	mpAlignmentSteering->getSteering();
	mpCohesionSteering->getSteering();
	mpSeperationSteering->getSteering();

	mLinear += (mpAlignmentSteering->getLinear() * 1) +(mpCohesionSteering->getLinear() * 1) + (mpSeperationSteering->getLinear() * 1.25f);
	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();

	mAngular = 0;

	return this;
}