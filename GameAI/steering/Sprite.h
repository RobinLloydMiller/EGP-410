//used with permission from Lucas Spiker

#ifndef _SPRITE_H
#define _SPRITE_H

#include "DeanLib/Vector2D.h"
#include "GraphicsBuffer.h"
#include "DeanLib/Trackable.h"

class Sprite : public Trackable
{
public:
	Vector2D getLoc();
	int getHeight();
	int getWidth();
	GraphicsBuffer* getBuffer();
	Sprite(GraphicsBuffer* buffer, float x, float y, float width, float height);
	~Sprite();

private:
	GraphicsBuffer* mpBuffer;
	int mWidth, mHeight;
	Vector2D mLoc;
};

#endif