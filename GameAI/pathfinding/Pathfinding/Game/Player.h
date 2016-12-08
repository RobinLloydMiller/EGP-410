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

private:
	int mScore = 0;
};

#endif