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
	ANGULAR_VELOCITY,
	MAX_ACCELERATION
};

class StateManager : public Trackable
{
public:
	StateManager() { mCurrState = DEBUG_ON; mCurrProperty = MAX_VELOCITY; }
	~StateManager() {}

	void setCurrState(GameState newState) { mCurrState = newState; }
	GameState getCurrState() { return mCurrState; }
	void setCurrProperty(EnemyProperty newProperty) { mCurrProperty = newProperty; }
	EnemyProperty getCurrProperty() { return mCurrProperty; }

private:
	GameState mCurrState;
	EnemyProperty mCurrProperty;

};

#endif