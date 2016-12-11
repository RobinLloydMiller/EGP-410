#ifndef _TILELAYER_H
#define _TILELAYER_H

#include "Trackable.h"
#include "Tile.h"
#include <sstream>

class TileLayer : public Trackable
{
public:
	TileLayer(std::string id, int width, int height, std::string tileString);
	~TileLayer();

	Tile* getTile(int x, int y);
	std::string getName() { return mID; };

private:
	Tile** mpTiles;
	int mWidth, mHeight;
	std::string mID;
};

#endif