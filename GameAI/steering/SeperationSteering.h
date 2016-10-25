#ifndef _SEPERATIONSTEERING_H
#define _SEPERATIONSTEERING_H

#include "Steering.h"

class KinematicUnit;

class SeperationSteering : public Steering
{
public:
	SeperationSteering(KinematicUnit* pMover);

	virtual Steering* getSteering();

private:
	//the radius in which a boid will start aligning with other boids
	const float mFlockRadius = 75;
	KinematicUnit* mpMover;
};

#endif