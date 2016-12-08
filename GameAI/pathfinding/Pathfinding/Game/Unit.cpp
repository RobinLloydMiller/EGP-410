#include "Unit.h"
#include "Animation.h"
#include "GameApp.h"
#include "Grid.h"
#include "GraphicsSystem.h"

Unit::Unit(float speed, float frameTime)
:mSpeed(speed), mPos(Vector2D(0,0)), mDir(Direction::NONE)
{
	mpAnime = new Animation(frameTime);
}

Unit::~Unit()
{
	delete mpAnime;
}

void Unit::update(double deltaTime)
{
	Vector2D newPos(0, 0);
	switch (mDir)
	{
	case Direction::LEFT:
		newPos = Vector2D(mPos.getX() - (mSpeed * deltaTime), mPos.getY());
		break;
	case Direction::RIGHT:
		newPos = Vector2D(mPos.getX() + (mSpeed * deltaTime), mPos.getY());
		break;
	case Direction::UP:
		newPos = Vector2D(mPos.getX(), mPos.getY() - (mSpeed * deltaTime));
		break;
	case Direction::DOWN:
		newPos = Vector2D(mPos.getX(), mPos.getY() + (mSpeed * deltaTime));
		break;
	default:
		newPos = mPos;
		break;
	}

	//if unit is going to be in a wall prevent the movement
	if (gpGameApp->getGrid()->isCollidingAtPixelXY(newPos.getX(), newPos.getY()) == Vector2D(-1, -1))
	{
		mPos = newPos;
	}

	//screen wrapping
	if (mPos.getX() < 0)
		mPos.setX(gpGameApp->getGraphicsSystem()->getWidth());
	else if (mPos.getX() > gpGameApp->getGraphicsSystem()->getWidth())
		mPos.setX(0);

	//screen wrapping
	if (mPos.getY() < 0)
		mPos.setY(gpGameApp->getGraphicsSystem()->getHeight());
	else if (mPos.getY() > gpGameApp->getGraphicsSystem()->getHeight())
		mPos.setY(0);

	mpAnime->update(deltaTime);
}

void Unit::draw(GraphicsBuffer & dest)
{
	mpAnime->draw(dest, mPos.getX(), mPos.getY());
}
