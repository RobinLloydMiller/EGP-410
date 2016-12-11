#ifndef _TILE_H
#define _TILE_H

#include "Trackable.h"

class Tile : public Trackable
{
public:
	Tile(int id);
	~Tile();


	int getID() { return mTileID; };

private:
	int mTileID;

};

#endif