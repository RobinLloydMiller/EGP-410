#ifndef _ENEMY_H
#define _ENEMY_H

#include "Unit.h"

class Enemy : public Unit
{
public:
	Enemy(float speed, float frameTime);
	~Enemy();

	void update(double deltaTime);
	void draw(GraphicsBuffer& dest);
};

#endif