#include "Animation.h"
#include "Sprite.h"

Animation::Animation(double frameTime)
{
	mFrameTime = frameTime;
	mTimeToSwitch = mFrameTime;
	mCurrentIndex = 0;
}

Animation::~Animation()
{
	for (auto &it : mSprites)
		delete it;

	mSprites.clear();
}

void Animation::update(double deltaTime)
{
	mTimeToSwitch -= deltaTime;
	if (mTimeToSwitch <= 0)
	{
		if (mCurrentIndex++ == mSprites.size() - 1)
			mCurrentIndex = 0;

		mCurrentSprite = mSprites[mCurrentIndex];
		mTimeToSwitch = mFrameTime;
	}
}

void Animation::draw(GraphicsBuffer& dest, float x, float y)
{
	if (mSprites.size() <= 0)
		return;

	mCurrentSprite->draw(dest, x, y);
}

void Animation::addSprite(Sprite* sprite)
{
	mSprites.push_back(sprite);
	mCurrentSprite = mSprites[0];
}

void Animation::addSprite(GraphicsBuffer * pBuffer, float sx, float sy, float sw, float sh)
{
	mSprites.push_back(new Sprite(pBuffer, sx, sy, sw, sh));
}