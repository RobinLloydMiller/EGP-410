#include "Player.h"
#include "GameApp.h"
#include "Grid.h"
#include "GridVisualizer.h"
#include "GraphicsBufferManager.h"
#include "GraphicsBuffer.h"
#include "Animation.h"
#include "Sprite.h"

Player::Player(float speed, float frameTime)
:Unit(speed, frameTime)
{
	GraphicsBufferManager* pBuffMan = gpGameApp->getGraphicsBufferManager();

	mpAnime->addSprite(new Sprite(pBuffMan->getBuffer(69), 0, 0, pBuffMan->getBuffer(69)->getWidth(), pBuffMan->getBuffer(69)->getHeight()));
	mpAnime->addSprite(new Sprite(pBuffMan->getBuffer(70), 0, 0, pBuffMan->getBuffer(70)->getWidth(), pBuffMan->getBuffer(70)->getHeight()));
}

Player::~Player()
{
}

void Player::update(double deltaTime)
{
	Unit::update(deltaTime);

	//check collision with coin
	Vector2D collPoint = gpGameApp->getGrid()->isCollidingAtPixelXY(mPos.getX(), mPos.getY(), 2);
	if (collPoint != Vector2D(-1, -1))
	{
		mScore++;
		gpGameApp->getGrid()->setValueAtPixelXY(collPoint.getX(), collPoint.getY(), 0);
		gpGameApp->getGridVisualizer()->setDirty();
	}
}

void Player::draw(GraphicsBuffer& dest)
{
	Unit::draw(dest);
}