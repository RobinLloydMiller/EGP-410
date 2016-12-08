#ifndef _PLAYER_H
#define _PLAYER_H

#include "Sprite.h"
#include "Vector2D.h"

class Animation;

enum class PlayerDirection
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Player : public Trackable
{
public:
	Player();
	~Player();

	Vector2D getPos() const { return mPos; }
	void setDir(PlayerDirection newDir) { mDir = newDir; }

	void update(double deltaTime);
	void draw(GraphicsBuffer& dest);

private:
	Animation* mpAnime;
	Vector2D mPos;
	PlayerDirection mDir;
	float mSpeed = 0.1f;
	int mScore = 0;
};

#endif