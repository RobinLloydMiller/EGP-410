#include "Player.h"
#include "GameApp.h"
#include "Grid.h"
#include "GridVisualizer.h"
#include "Animation.h"
#include "GraphicsBufferManager.h"
#include "GraphicsBuffer.h"

Player::Player()
{
	GraphicsBufferManager* pBuffMan = gpGameApp->getGraphicsBufferManager();

	mPos = Vector2D(0, 0);
	mDir = PlayerDirection::RIGHT;

	mpAnime = new Animation(0.33);
	mpAnime->addSprite(new Sprite(pBuffMan->getBuffer(69), 0, 0, pBuffMan->getBuffer(69)->getWidth(), pBuffMan->getBuffer(69)->getHeight()));
	mpAnime->addSprite(new Sprite(pBuffMan->getBuffer(70), 0, 0, pBuffMan->getBuffer(70)->getWidth(), pBuffMan->getBuffer(70)->getHeight()));
}

Player::~Player()
{
	delete mpAnime;
}

void Player::update(double deltaTime)
{
	Vector2D newPos(0,0);
	switch (mDir)
	{
	case PlayerDirection::LEFT:
		newPos = Vector2D(mPos.getX() - (mSpeed * deltaTime), mPos.getY());
		break;
	case PlayerDirection::RIGHT:
		newPos = Vector2D(mPos.getX() + (mSpeed * deltaTime), mPos.getY());
		break;
	case PlayerDirection::UP:
		newPos = Vector2D(mPos.getX(), mPos.getY() - (mSpeed * deltaTime));	
		break;
	case PlayerDirection::DOWN:
		newPos = Vector2D(mPos.getX(), mPos.getY() + (mSpeed * deltaTime));
		break;
	default:
		break;
	}

	//check if space player is going to move to is empty
	//(-1, -1) is returned if no collision is happening
	if (gpGameApp->getGrid()->isCollidingAtPixelXY(newPos.getX(), newPos.getY()) == Vector2D(-1, -1))
	{
		mPos = newPos;


		Vector2D collPoint = gpGameApp->getGrid()->isCollidingAtPixelXY(mPos.getX(), mPos.getY(), 2);
		if (collPoint != Vector2D(-1, -1))
		{
			mScore++;
			gpGameApp->getGrid()->setValueAtPixelXY(collPoint.getX(), collPoint.getY(), 0);
			gpGameApp->getGridVisualizer()->setDirty();
		}
	}

	if (mPos.getX() < 0)
		mPos.setX(gpGameApp->getGraphicsSystem()->getWidth());
	else if (mPos.getX() > gpGameApp->getGraphicsSystem()->getWidth())
		mPos.setX(0);

	if (mPos.getY() < 0)
		mPos.setY(gpGameApp->getGraphicsSystem()->getHeight());
	else if (mPos.getY() > gpGameApp->getGraphicsSystem()->getHeight())
		mPos.setY(0);

	mpAnime->update(deltaTime);
}

void Player::draw(GraphicsBuffer& dest)
{
	mpAnime->draw(dest, mPos.getX(), mPos.getY());
}