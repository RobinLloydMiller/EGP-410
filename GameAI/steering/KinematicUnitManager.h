#ifndef _UNITMANAGER_H
#define _UNITMANAGER_H

#include "KinematicUnit.h"
#include <vector>

//UnitManager - manager class that creates, destroys, and updates kinematic units. Also holds pointers to all kinematic units in game
//Duncan

class KinematicUnitManager : public Trackable
{
public:
	KinematicUnitManager() {};
	~KinematicUnitManager();
	//returns true on success, false on failure
	bool addUnit(Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f);
	//this has to be size_t becuase it get compared to vector.size() which returns something thats not comparable to an int
	bool deleteUnit(size_t index);
	//deletes a random unit if no index is given
	bool deleteUnit();
	bool addPlayer(Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f);

	void updateMaxVelocity(float vel);
	void updateMaxAcceleration(float accel);
	void updateReactionRadius(float radius);
	void updateAngularVelocity(float angVel);
	
	//getter functions
	KinematicUnit* getPlayer() { return mpPlayer; };
	KinematicUnit* getUnit(int index) { return mUnits[index]; };
	int getUnitCount() { return mUnits.size(); }; //this count is excluding the player

	//updates all units
	void update(float time);
	//draws all units
	void draw(GraphicsBuffer* pBuffer);

private:
	std::vector<KinematicUnit*> mUnits;
	//seperate pointer to player to make deleing non-player units easier
	KinematicUnit* mpPlayer;
	
};

#endif