//used with permission from Lucas Spiker

#include "Sprite.h"

Vector2D Sprite::getLoc()
{
	return mLoc;
}

int Sprite::getHeight()
{
	return mHeight;
}

int Sprite::getWidth()
{
	return mWidth;
}

GraphicsBuffer* Sprite::getBuffer()
{
	return mpBuffer;
}

Sprite::Sprite(GraphicsBuffer* buffer, float x, float y, float width, float height)
{
	mpBuffer = buffer;
	mLoc = Vector2D(x, y);
	mWidth = width;
	mHeight = height;
}

Sprite::~Sprite() {}