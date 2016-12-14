#include "Unit.h"
#include "Animation.h"
#include "GameApp.h"
#include "Grid.h"
#include "GraphicsSystem.h"
#include "Level.h"

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

	moveAndCheckCollision(newPos);
	
	//screen wrapping
	if (mPos.getX() + 2 < 0)
		mPos.setX(gpGameApp->getGraphicsSystem()->getWidth());
	else if (mPos.getX() + 2> gpGameApp->getGraphicsSystem()->getWidth())
		mPos.setX(0);

	//screen wrapping
	if (mPos.getY() + 2 < 0)
		mPos.setY(gpGameApp->getGraphicsSystem()->getHeight());
	else if (mPos.getY() + 2> gpGameApp->getGraphicsSystem()->getHeight())
		mPos.setY(0);

	mpAnime->update(deltaTime);
}

void Unit::draw(GraphicsBuffer & dest)
{
	mpAnime->draw(dest, mPos.getX(), mPos.getY());
}


//returns true on collision
bool Unit::moveAndCheckCollision(Vector2D newPos)
{
	int tileWidth, tileHeight;
	Level* pLevel = gpGameApp->getLevel();
	pLevel->getTileSize(tileWidth, tileHeight);
	int collBuffer = tileWidth / 8;

	int tileID1 = pLevel->getTile(newPos.getX() / tileWidth, newPos.getY() / tileHeight, "Collision")->getID();
	int tileID2 = pLevel->getTile((newPos.getX() + tileWidth - collBuffer) / tileWidth, newPos.getY() / tileHeight, "Collision")->getID();
	int tileID3 = pLevel->getTile(newPos.getX() / tileWidth, (newPos.getY() + tileHeight - collBuffer) / tileHeight, "Collision")->getID();
	int tileID4 = pLevel->getTile((newPos.getX() + tileWidth - collBuffer)/ tileWidth, (newPos.getY() + tileHeight - collBuffer) / tileHeight, "Collision")->getID();

	//if unit is going to be in a wall prevent the movement
	if (tileID1 == 0 && tileID2 == 0 && tileID3 == 0 && tileID4 == 0)
	{
		mPos = newPos;
		return false;
	}
	return true;
}