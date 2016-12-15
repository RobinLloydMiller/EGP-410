#ifndef _PLAYER_H
#define _PLAYER_H

#include "Unit.h"
#include "StateMachine.h"

class StateMachine;
class StateMachineState;
class StateTransition;

class Player : public Unit
{
public:
	Player(float speed, float frameTime);
	~Player();

	void update(double deltaTime);
	void draw(GraphicsBuffer& dest);

	void respawn() { mPos = mSpawnPos; }

	bool isInvincible() const { return mInvincible; }
	void setInvincible(bool invincible) { mInvincible = invincible; }
	int getPlayerStateId()  const { return mpStateMachine->getCurrentState()->getID(); }

private:
	int mScore = 0;
	Vector2D mSpawnPos = Vector2D(1, 1);
	bool mInvincible = false;

	StateMachine* mpStateMachine;
	StateMachineState* mpNoCandyState, *mpCandyState;
	StateTransition* mpToNoCandyState, *mpToCandyState;

	void initStateMachine();
};

#endif