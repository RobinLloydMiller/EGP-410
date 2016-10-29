#ifndef _BOIDSSTEERING_H
#define _BOIDSSTEERING_H

/*******************************************************************************************
*  ________  ___  ________          ________  ________  ________  ________  ________       *
* |\   __  \|\  \|\   ____\        |\   __  \|\   __  \|\   __  \|\   __  \|\   __  \      *
* \ \  \|\ /\ \  \ \  \___|        \ \  \|\  \ \  \|\  \ \  \|\  \ \  \|\  \ \  \|\  \     *
*  \ \   __  \ \  \ \  \  ___       \ \   ____\ \  \\\  \ \   ____\ \   ____\ \   __  \    *
*   \ \  \|\  \ \  \ \  \|\  \       \ \  \___|\ \  \\\  \ \  \___|\ \  \___|\ \  \ \  \   *
*    \ \_______\ \__\ \_______\       \ \__\    \ \_______\ \__\    \ \__\    \ \__\ \__\  *
*     \|_______|\|__|\|_______|        \|__|     \|_______|\|__|     \|__|     \|__|\|__|  *
*                                                                                          * 
*******************************************************************************************/

//the class that manages all three boids steering behaviors

#include "Steering.h"

class KinematicUnit;
class AlignmentSteering;
class CohesionSteering;
class SeperationSteering;

class BoidsSteering : public Steering
{
	public:
		BoidsSteering(KinematicUnit* pMover);
		~BoidsSteering();

		virtual Steering* getSteering();

	private:
		AlignmentSteering* mpAlignmentSteering;
		CohesionSteering* mpCohesionSteering;
		SeperationSteering* mpSeperationSteering;
		KinematicUnit* mpMover;
		Vector2D mWanderTarget;
		const float mWanderTargetRadius = 200;
};

#endif
