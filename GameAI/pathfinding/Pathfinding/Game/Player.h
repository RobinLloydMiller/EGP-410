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

	void setPos(Vector2D pos) { mPos = pos; mSpawnPos = pos; }
	bool isInvincible() const { return mInvincible; }
	void setInvincible(bool invincible) { mInvincible = invincible; }
	int getPlayerStateId()  const { return mpStateMachine->getCurrentState()->getID(); }

	void noCandyColor();
	void candyColor();

private:
	int mScore = 0;
	Vector2D mSpawnPos = Vector2D(700, 700);
	bool mInvincible = false;

	StateMachine* mpStateMachine;
	StateMachineState* mpNoCandyState, *mpCandyState;
	StateTransition* mpToNoCandyState, *mpToCandyState;

	Animation* mpCandyAnime, *mpNoCandyAnime;

	void initStateMachine();
};

#endif