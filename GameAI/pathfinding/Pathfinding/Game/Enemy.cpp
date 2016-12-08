#include "Enemy.h"
#include "Animation.h"
#include "GameApp.h"
#include "Sprite.h"
#include "GraphicsBufferManager.h"
#include "GraphicsBuffer.h"

Enemy::Enemy(float speed, float frameTime)
:Unit(speed, frameTime)
{
	GraphicsBufferManager* pBuffMan = gpGameApp->getGraphicsBufferManager();

	mpAnime->addSprite(new Sprite(pBuffMan->getBuffer(71), 0, 0, pBuffMan->getBuffer(71)->getWidth(), pBuffMan->getBuffer(71)->getHeight()));

	mPos = Vector2D(32, 32);
}

Enemy::~Enemy()
{
}

void Enemy::update(double deltaTime)
{

	//getem

	Unit::update(deltaTime);
}

void Enemy::draw(GraphicsBuffer& dest)
{
	Unit::draw(dest);
}