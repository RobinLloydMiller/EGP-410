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
	/*if (getDistance(mpMover->getPosition(), mWanderTarget) > mWanderTargetRadius)
	{
		mLinear = mWanderTarget - mpMover->getPosition();
		mLinear.normalize();
		mLinear *= mpMover->getMaxVelocity();
		mAngular = 0;
	}
	else
	{
		newWanderTarget();
	}*/

	mpAlignmentSteering->getSteering();
	mpCohesionSteering->getSteering();
	mpSeperationSteering->getSteering();

	mLinear += mpAlignmentSteering->getLinear() + mpCohesionSteering->getLinear() + mpSeperationSteering->getLinear();
	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();

	return this;
}