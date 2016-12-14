#ifndef _UNIT_H
#define _UNIT_H

#include "Trackable.h"
#include "Vector2D.h"

class Animation;
class GraphicsBuffer;

enum class Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
};

class Unit : public Trackable
{
public:
	Unit(float speed, float frameTime);
	virtual ~Unit();

	Vector2D getPos() const { return mPos; }
	void setDir(Direction newDir) { mDir = newDir; }

	void update(double deltaTime);
	void draw(GraphicsBuffer& dest);

protected:
	bool moveAndCheckCollision(Vector2D newPos);

	Animation* mpAnime;
	Vector2D mPos;
	Direction mDir;
	float mSpeed;
};

#endif