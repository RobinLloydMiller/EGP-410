#ifndef _CIRCLECOLLIDER_H
#define _CIRCLECOLLIDER_H

#include "Trackable.h"
#include "Vector2D.h"

class BoxCollider;

class CircleCollider : public Trackable
{
public:
	CircleCollider(Vector2D pos, float radius = 16.0f);
	~CircleCollider() {}

	bool checkCollision(BoxCollider* coll);
	bool checkCollision(CircleCollider* coll);

	Vector2D getPos() const { return mPos; }
	float getRadius() const { return mRadius; }

	//keep circle positioned on unit center
	void update(Vector2D deltaDistance);

private:
	float mRadius;
	//center of the circle
	Vector2D mPos;
};

#endif