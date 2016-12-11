#ifndef _PLAYER_H
#define _PLAYER_H

#include "Unit.h"

class Player : public Unit
{
public:
	Player(float speed, float frameTime);
	~Player();

	void update(double deltaTime);
	void draw(GraphicsBuffer& dest);

	void respawn() { mPos = mSpawnPos; }

private:
	int mScore = 0;
	Vector2D mSpawnPos = Vector2D(32, 32);
};

#endif