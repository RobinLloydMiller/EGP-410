#include "TileLayer.h"

TileLayer::TileLayer(std::string id, int width, int height, std::string tileString)
{
	int size = 0;

	mID = id;
	mWidth = width;
	mHeight = height;

	mpTiles = new Tile*[mWidth * mHeight];

	std::stringstream ss(tileString);

	int tmp;
	std::string junk;
	for (int i = 0; i < mHeight; i++)
	{
		for (int j = 0; j < mWidth; j++)
		{
			std::getline(ss, junk, ',');
			tmp = stoi(junk);
			Tile* tmpTile = new Tile(tmp);
			mpTiles[(i * mWidth) + j] = tmpTile;
			size++;
			//std::cout << (i*mHeight) + j << ", ";

		}
		//std::cout << std::endl;
	}

	/*for (int i = 0; i < mHeight; i++)
	{
		for (int j = 0; j < mWidth; j++)
		{
			std::cout << mpTiles[i * mHeight + j]->getID() << ", ";
		}
		std::cout << std::endl;
	}*/
}

TileLayer::~TileLayer()
{
	for (int i = 0; i < mWidth*mHeight; i++)
	{
		delete mpTiles[i];
	}

	delete[] mpTiles;
}

Tile* TileLayer::getTile(int x, int y)
{
	return mpTiles[y * mWidth + x];
}