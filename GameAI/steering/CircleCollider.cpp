#include "CircleCollider.h"
#include "BoxCollider.h"
#include <cmath>

CircleCollider::CircleCollider(Vector2D pos, float radius)
:mRadius(radius), mPos(pos)
{
}

void CircleCollider::update(Vector2D deltaDistance)
{
	mPos += deltaDistance;
}

bool CircleCollider::checkCollision(BoxCollider* coll)
{
	//thanks for the help http://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
	//used center of circle and center of rectangle to calculate if circle is close enough to intersect with rectangle

	Vector2D rectCenter(coll->getCenter().getX(), coll->getCenter().getY());
	float rectWidth = coll->getWidth();
	float rectHeight = coll->getHeight();

	Vector2D circleDistance(std::abs(mPos.getX() - rectCenter.getX()), std::abs(mPos.getY() - rectCenter.getY()));

	if (circleDistance.getX() > (rectWidth / 2 + mRadius))
		return false;
	if (circleDistance.getY() > (rectHeight / 2 + mRadius))
		return false;

	if (circleDistance.getX() <= (rectWidth / 2))
		return true;
	if (circleDistance.getY() <= (rectHeight / 2))
		return true;

	float cornerDistance_sq = (std::pow((circleDistance.getX() - rectWidth / 2), 2)) + (std::pow(circleDistance.getY() - rectHeight/2, 2));

	return (cornerDistance_sq <= (std::pow(mRadius, 2)));
}

bool CircleCollider::checkCollision(CircleCollider* coll)
{
	//thanks for the help http://stackoverflow.com/questions/1736734/circle-circle-collision
	return (std::pow(coll->getPos().getX() - mPos.getX(), 2)) + (std::pow(mPos.getY() - coll->getPos().getY(), 2)) <= std::pow(mRadius + coll->getRadius(), 2);
}