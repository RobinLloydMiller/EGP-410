#pragma once

#include "Steering.h"
#include <algorithm>

class KinematicUnit;

const float MAX_WANDER_ROTATION = 3.5f;

class KinematicWanderSteering:public Steering
{
public:
	KinematicWanderSteering( KinematicUnit* pMover );
	~KinematicWanderSteering(){};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
};