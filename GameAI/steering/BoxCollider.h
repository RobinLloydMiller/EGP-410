#ifndef _BOXCOLLIDER_H
#define _BOXCOLLIDER_H

#include "Trackable.h"
#include "Vector2D.h"

class BoxCollider : public Trackable
{
public:
	BoxCollider(Vector2D topCorner, Vector2D bottomCorner);
	~BoxCollider();

	Vector2D getTopCorner() { return mTopLeftCorner; }
	Vector2D getBottomCorner() { return mBottomRightCorner; }

	bool checkCollision(BoxCollider* coll);
	void update(Vector2D deltaDistance);

private:
	Vector2D mTopLeftCorner, mBottomRightCorner;

};

#endif