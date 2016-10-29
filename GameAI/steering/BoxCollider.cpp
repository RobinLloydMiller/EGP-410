#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2D topCorner, Vector2D bottomCorner)
:mTopLeftCorner(topCorner), mBottomRightCorner(bottomCorner)
{
}

BoxCollider::~BoxCollider()
{
}

//calculates center using width length and adding half to the corrdinates of the top left corner
Vector2D BoxCollider::getCenter() const
{
	Vector2D center;

	float x = mBottomRightCorner.getX() - mTopLeftCorner.getX();
	float y = mBottomRightCorner.getY() - mTopLeftCorner.getY();

	center.setX(mTopLeftCorner.getX() + (x / 2));
	center.setY(mTopLeftCorner.getY() + (y / 2));

	return center;
}

float BoxCollider::getWidth() const
{
	return mBottomRightCorner.getX() - mTopLeftCorner.getX();
}

float BoxCollider::getHeight() const
{
	return mBottomRightCorner.getY() - mTopLeftCorner.getY();;
}

//check if bound of rectangles intersect with each other
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