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

	mpAnime = new Animation(50.0);
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
		newPos = Vector2D(mPos.getX() - mSpeed, mPos.getY());
		break;
	case PlayerDirection::RIGHT:
		newPos = Vector2D(mPos.getX() + mSpeed, mPos.getY());
		break;
	case PlayerDirection::UP:
		newPos = Vector2D(mPos.getX(), mPos.getY() - mSpeed);	
		break;
	case PlayerDirection::DOWN:
		newPos = Vector2D(mPos.getX(), mPos.getY() + mSpeed);
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

	mpAnime->update(deltaTime);
}

void Player::draw(GraphicsBuffer& dest)
{
	mpAnime->draw(dest, mPos.getX(), mPos.getY());
}