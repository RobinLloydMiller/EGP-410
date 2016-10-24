#include "BoidsSteering.h"
#include "AlignmentSteering.h"
#include "CohesionSteering.h"
#include "SeperationSteering.h"
#include "KinematicUnit.h"

BoidsSteering::BoidsSteering(KinematicUnit* pMover)
:mpMover(pMover)
{
	mpAlignmentSteering = new AlignmentSteering(pMover);
	mpCohesionSteering = new CohesionSteering(pMover);
	mpSeperationSteering = new SeperationSteering(pMover);

	newWanderTarget();
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

	mpAlignmentSteering->getSteering();
	mpCohesionSteering->getSteering();
	mpSeperationSteering->getSteering();

	mLinear += (mpAlignmentSteering->getLinear() * 3) +(mpCohesionSteering->getLinear() * 1) + (mpSeperationSteering->getLinear() * 3);
	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();

	return this;
}