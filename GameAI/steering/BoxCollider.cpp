#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2D topCorner, Vector2D bottomCorner)
:mTopLeftCorner(topCorner), mBottomRightCorner(bottomCorner)
{
}

BoxCollider::~BoxCollider()
{
}

bool BoxCollider::checkCollision(BoxCollider * coll)
{
	if (mBottomRightCorner.getX() < coll->getTopCorner().getX())
		return false;
	if (mTopLeftCorner.getX() > coll->getBottomCorner().getX())
		return false;
	if (mBottomRightCorner.getY() < coll->getTopCorner().getY())
		return false;
	if (mTopLeftCorner.getY() > coll->getBottomCorner().getY())
		return false;

	return true;
}

void BoxCollider::update(Vector2D deltaDistance)
{
	mTopLeftCorner += deltaDistance;
	mBottomRightCorner += deltaDistance;

	//std::cout << "y: " << mTopLeftCorner.getY() << std::endl;

}