#include "Player.h"
#include "GameApp.h"
#include "Grid.h"
#include "GridVisualizer.h"

Player::Player(GraphicsBuffer * pBuffer, float srcX, float srcY, float width, float height)
:Sprite(pBuffer, srcX, srcY, width, height)
,mPos(0, 0), mDir(PlayerDirection::RIGHT)
{
}

void Player::update()
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
}