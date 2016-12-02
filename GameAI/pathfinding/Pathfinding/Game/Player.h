#ifndef _PLAYER_H
#define _PLAYER_H

#include "Sprite.h"
#include "Vector2D.h"

class Player : public Sprite
{
public:
	Player( GraphicsBuffer* pBuffer, float srcX, float srcY, float width, float height );
	~Player() {}

	Vector2D getPos() { return mPos; }

private:
	Vector2D mPos;
};

#endif