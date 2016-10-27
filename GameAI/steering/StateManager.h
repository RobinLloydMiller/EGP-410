#ifndef _STATEMANAGER_H
#define _STATEMANAGER_H

#include "Trackable.h"

enum GameState
{
	DEBUG_ON,
	DEBUG_OFF
};

enum EnemyProperty
{
	MAX_VELOCITY,
	REACTION_RADIUS,
	ROTATIONAL_VELOCITY,
	MAX_ACCELERATION,
	ALIGNMENT_WEIGHT,
	COHESION_WEIGHT,
	SEPERATION_WEIGHT
};

class StateManager : public Trackable
{
public:
	StateManager() { mCurrState = DEBUG_ON; mCurrProperty = MAX_VELOCITY; loadData(); }
	~StateManager() {}

	void setCurrState(GameState newState) { mCurrState = newState; }
	GameState getCurrState() { return mCurrState; }
	void setCurrProperty(EnemyProperty newProperty) { mCurrProperty = newProperty; }
	EnemyProperty getCurrProperty() { return mCurrProperty; }

	void saveData();
	void loadData();

	//update boids weights
	inline void setAlignmentWeight(float alignment) { mAlignmentWeight = alignment; }
	inline void setCohesionWeight(float cohesion) { mCohesionWeight = cohesion; }
	inline void setSeperationWeight(float seperation) { mSeperationWeight = seperation; }

	//getters for boids weights
	inline float getAlignmentWeight() const { return mAlignmentWeight; }
	inline float getCohesionWeight() const { return mCohesionWeight; }
	inline float getSeperationWeight() const { return mSeperationWeight; }

private:
	GameState mCurrState;
	EnemyProperty mCurrProperty;
	float mAlignmentWeight = 1.0f, mCohesionWeight = 1.0f, mSeperationWeight = 3.0f;

};

#endif