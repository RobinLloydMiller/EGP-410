#ifndef _WANDERANDSEEKSTEERING_H
#define _WANDERANDSEEKSTEERING_H

#include "Steering.h"
#include "KinematicUnit.h"
#include "DynamicSeekSteering.h"
#include "KinematicWanderSteering.h"
#include <cmath>
#include <cstdlib>

class WanderAndSeekSteering : public Steering
{
public:
	WanderAndSeekSteering(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee = false);
	~WanderAndSeekSteering() {};

	virtual Steering* getSteering();

private:
	bool mShouldFlee;
	void newWanderTarget() { mWanderTarget = Vector2D(rand() % 1024, rand() % 768); }
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	Vector2D mWanderTarget;
	const float mWanderTargetRadius = 200;
};

#endif