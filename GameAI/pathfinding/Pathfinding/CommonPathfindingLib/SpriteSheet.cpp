#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(std::string path, int width, int height, int tWidth, int tHeight, int tileCount, int columns)
{
	mpBuffer = new GraphicsBuffer(path);

	mWidth = width;
	mHeight = height;
	mTileWidth = tWidth;
	mTileHeight = tHeight;
	mTileCount = tileCount;
	mColumns = columns;
	mRows = mTileCount / mColumns;
}

SpriteSheet::~SpriteSheet()
{
	delete mpBuffer;
}

GraphicsBuffer* SpriteSheet::getBuffer()
{
	return mpBuffer;
}