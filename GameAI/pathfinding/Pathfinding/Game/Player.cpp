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
	if (!gpGameApp->getGrid()->isCollidingAtPixelXY(newPos.getX(), newPos.getY()))
	{
		mPos = newPos;
		if (gpGameApp->getGrid()->isCollidingAtPixelXY(mPos.getX(), mPos.getY(), 2))
		{
			mScore++;
			std::cout << "Score: " << mScore << std::endl;
			//gpGameApp->getGrid()->setValueAtPixelXY(mPos.getX(), mPos.getY(), 0);
			gpGameApp->getGrid()->setValueAtPixelXY(64, 64, 0);
			gpGameApp->getGridVisualizer()->setDirty();
		}
	}
}