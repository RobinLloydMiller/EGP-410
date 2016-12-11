#ifndef _SPRITESHEET_H
#define _SPRITESHEET_H

#include <string>
#include "graphicsBuffer.h"

class SpriteSheet : public Trackable
{
public:
	SpriteSheet(std::string path, int width, int height, int tWidth, int tHeight, int tileCount, int columns);
	~SpriteSheet();

	GraphicsBuffer* getBuffer();

private:
	int mWidth, mHeight;
	int mTileWidth, mTileHeight;
	int mTileCount;
	int mRows, mColumns;
	GraphicsBuffer* mpBuffer;
};

#endif