#ifndef _ANIMATION_H
#define _ANIMATION_H

#include "Trackable.h"
#include <vector>

class GraphicsBuffer;
class Sprite;

class Animation : public Trackable
{
public:
	Animation(double frameTime);
	~Animation();

	void update(double deltaTime);
	void draw(GraphicsBuffer& dest, float x, float y);
	void addSprite(Sprite* sprite);
	void addSprite(GraphicsBuffer* pBuffer, float sx, float sy, float sw, float sh);

private:
	size_t mCurrentIndex;
	double mFrameTime, mTimeToSwitch;
	std::vector<Sprite*> mSprites;
	Sprite* mCurrentSprite;
};

#endif