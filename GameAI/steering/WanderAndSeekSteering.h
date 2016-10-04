#ifndef _WANDERANDSEEKSTEERING_H
#define _WANDERANDSEEKSTEERING_H

#include "Steering.h"
#include "KinematicUnit.h"
#include "DynamicSeekSteering.h"
#include "KinematicWanderSteering.h"
#include <cmath>

class WanderAndSeekSteering : public Steering
{
public:
	WanderAndSeekSteering(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee = false);
	~WanderAndSeekSteering() {};

	virtual Steering* getSteering();

private:
	bool mShouldFlee;
	float getDistance(Vector2D pos, Vector2D pos2);
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	const float SEEK_RADIUS = 200;
};

#endif