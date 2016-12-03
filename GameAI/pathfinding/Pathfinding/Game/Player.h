#ifndef _PLAYER_H
#define _PLAYER_H

#include "Sprite.h"
#include "Vector2D.h"

enum class PlayerDirection
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Player : public Sprite
{
public:
	Player( GraphicsBuffer* pBuffer, float srcX, float srcY, float width, float height );
	~Player() {}

	Vector2D getPos() const { return mPos; }
	void setDir(PlayerDirection newDir) { mDir = newDir; }

	void update();

private:
	Vector2D mPos;
	PlayerDirection mDir;
	float mSpeed = 0.1f;
};

#endif