#ifndef _COHESIONSTEERING_H
#define _COHESIONSTEERING_H

#include "Steering.h"

class KinematicUnit;

class CohesionSteering : public Steering
{
public:
	CohesionSteering(KinematicUnit* pMover);

	virtual Steering* getSteering();

private:
	//the radius in which a boid will start aligning with other boids
	const float mFlockRadius = 200;
	int mBoidCount = 0;
	KinematicUnit* mpMover;
};

#endif