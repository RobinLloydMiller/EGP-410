#ifndef _BOXCOLLIDER_H
#define _BOXCOLLIDER_H

#include "Trackable.h"
#include "Vector2D.h"

class BoxCollider : public Trackable
{
public:
	BoxCollider(Vector2D topCorner, Vector2D bottomCorner);
	~BoxCollider();

	Vector2D getTopCorner() const { return mTopLeftCorner; }
	Vector2D getBottomCorner() const { return mBottomRightCorner; }
	Vector2D getCenter() const;
	float getWidth() const;
	float getHeight() const;

	bool checkCollision(BoxCollider* coll);
	void update(Vector2D deltaDistance);

private:
	Vector2D mTopLeftCorner, mBottomRightCorner;

};

#endif