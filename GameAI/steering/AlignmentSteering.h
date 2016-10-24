#ifndef _ALIGNMENT_H
#define _ALIGNMENT_H

#include "Steering.h"

class KinematicUnit;

class AlignmentSteering : public Steering
{
	public:
		AlignmentSteering(KinematicUnit* pMover);

		virtual Steering* getSteering();

	private:
		//the radius in which a boid will start aligning with other boids
		const float mFlockRadius = 200;
		KinematicUnit* mpMover;
};

#endif