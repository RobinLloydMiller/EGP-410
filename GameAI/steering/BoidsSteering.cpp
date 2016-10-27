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
	mLinear = Vector2D();

	mpAlignmentSteering->getSteering();
	mpCohesionSteering->getSteering();
	mpSeperationSteering->getSteering();

	mLinear += (mpAlignmentSteering->getLinear() * gpGame->getStateManager()->getAlignmentWeight()) +(mpCohesionSteering->getLinear() * gpGame->getStateManager()->getCohesionWeight()) + (mpSeperationSteering->getLinear() * gpGame->getStateManager()->getSeperationWeight());
	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();

	mAngular = 0;

	return this;
}