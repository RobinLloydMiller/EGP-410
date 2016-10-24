#ifndef _BOIDSSTEERING_H
#define _BOIDSSTEERING_H

/***********************************************
* ______ _        ______                        *
* | ___ (_)       | ___ \                       *
* | |_/ /_  __ _  | |_/ /__  _ __  _ __   __ _  *
* | ___ \ |/ _` | |  __/ _ \| '_ \| '_ \ / _` | *
* | |_/ / | (_| | | | | (_) | |_) | |_) | (_| | *
* \____/|_|\__, | \_|  \___/| .__/| .__/ \__,_| *
*          _ _/ |           | |   | |           *
*          |___/            |_|   |_|           *
************************************************/

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
		void newWanderTarget() { mWanderTarget = Vector2D(rand() % 1024, rand() % 768); std::cout << mWanderTarget.getX() << std::endl; }

		AlignmentSteering* mpAlignmentSteering;
		CohesionSteering* mpCohesionSteering;
		SeperationSteering* mpSeperationSteering;
		KinematicUnit* mpMover;
		Vector2D mWanderTarget;
		const float mWanderTargetRadius = 200;
};

#endif
