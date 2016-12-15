#include "Grid.h"
#include "GraphicsSystem.h"
#include "Vector2D.h"
#include "Game.h"
#include "Level.h"
#include <memory.h>

Grid::Grid( int pixelWidth, int pixelHeight, int squareSize )
:mPixelWidth(pixelWidth)
,mPixelHeight(pixelHeight)
,mSquareSize(squareSize)
{
	mGridWidth = pixelWidth / squareSize;
	mGridHeight = pixelHeight / squareSize;
	mpValues = new int[ mGridWidth * mGridHeight ];
	memset( mpValues, 0, sizeof(int) * mGridWidth * mGridHeight  );
}

Grid::~Grid()
{
	delete [] mpValues;
}

int Grid::getSquareIndexFromPixelXY( int x, int y ) const
{
	x /= mSquareSize;
	y /= mSquareSize;
	return y * mGridWidth + x;
}

int Grid::getValueAtIndex( int index ) const
{
	if (index >= 0 && index < mGridWidth*mGridHeight)
	{
		return *(mpValues + index);
	}
	else
	{
		return CLEAR_VALUE;
	}
}

int Grid::getValueAtPixelXY( int x, int y ) const
{
	int index = getSquareIndexFromPixelXY( x, y );
	return getValueAtIndex( index );
}

//returns the point of collision and (-1, -1) on no collision
Vector2D Grid::isCollidingAtPixelXY( int x, int y, int value) const
{
	//0 138 155 131 145 140 268 219

	int i = 5;

	int index = getValueAtPixelXY(x + i, y + i);
	int index2 = getValueAtPixelXY(x + mSquareSize - i, y + i);
	int index3 = getValueAtPixelXY(x + i, y + mSquareSize - i);
	int index4 = getValueAtPixelXY(x + mSquareSize - i, y + mSquareSize - i);

	//std::cout << x + mSquareSize - i << " " << y + mSquareSize - i << std::endl;

	if (value == 1)
	{
		std::cout << index4 << " ";
		if (!(index == 138 || index == 155 || index == 131 || index == 145 || index == 140 || index == 268 || index == 219 || index == 0))
		{
			
			return Vector2D(x + i, y + i);	
		}
		if (!(index2 == 138 || index2 == 155 || index2 == 131 || index2 == 145 || index2 == 140 || index2 == 268 || index2 == 219 || index2 == 0))
		{
			
			return Vector2D(x + mSquareSize - i, y + i);
		}
		if (!(index3 == 138 || index3 == 155 || index3 == 131 || index3 == 145 || index3 == 140 || index3 == 268 || index3 == 219 || index3 == 0))
		{
			
			return Vector2D(x + i, y + mSquareSize - i);
		}
		if (!(index4 == 138 || index4 == 155 || index4 == 131 || index4 == 145 || index4 == 140 || index4 == 268 || index4 == 219 || index4 == 0))
		{
			
			return Vector2D(x + mSquareSize - i, y + mSquareSize - i);
		}


		return Vector2D(-1, -1);
	}

	if (index == value)
		return Vector2D(x + i, y + i);
	if (index2 == value)
		return Vector2D(x + mSquareSize - i, y + i);
	if (index3 == value)
		return Vector2D(x + i, y + mSquareSize - i);
	if (index4 == value)
		return Vector2D(x + mSquareSize - i, y + mSquareSize - i);

	return Vector2D(-1, -1);
}
	
void Grid::setValueAtIndex( int index, int value )
{
	if (index >= 0 && index < mGridWidth*mGridHeight)
	{
		*(mpValues + index) = value;
	}
}

void Grid::setValueAtPixelXY( int x, int y, int value )
{
	int index = getSquareIndexFromPixelXY( x, y );
	setValueAtIndex( index, value );
}

Vector2D Grid::getULCornerOfSquare( int index ) const
{
	int squareY = index / mGridWidth;
	int squareX = index % mGridWidth;
	Vector2D pos( (float)(squareX * mSquareSize), (float)(squareY * mSquareSize) );
	return pos;
}

//get adjacent grid square indices
std::vector<int> Grid::getAdjacentIndices( int theSquareIndex ) const
{
	std::vector<int> indices;

	//make this 8 for using diagonal connections
	static const int NUM_DIRS = 4;
	//uses diagonal connections
	//						        N  NE	E  SE	S	SW	 W	NW
	//static int xMods[NUM_DIRS] = {	0,	1,	1,	1,	0,	-1,	-1,	-1 };
	//static int yMods[NUM_DIRS] = { -1, -1,	0,	1,	1,	 1,	 0,	-1 };


	//removes diagonal connections
	static int xMods[NUM_DIRS] = { 0,	1,	0,	-1};
	static int yMods[NUM_DIRS] = { -1, 	0,	1,	 0 };

	//find the x,y of the passed in index
	int x = theSquareIndex % mGridWidth;
	int y = theSquareIndex / mGridWidth;

	for( int i=0; i<NUM_DIRS; i++ )
	{
		//calc adjacent x,y
		int adjX = x + xMods[i];
		int adjY = y + yMods[i];

		//convert back to an index if on the Grid
		if( adjX >= 0 && adjX < mGridWidth && adjY >=0 && adjY < mGridHeight )
		{
			int adjIndex = ( adjY * mGridWidth ) + adjX;

			//add to vector of indices
			indices.push_back( adjIndex );
		}
	}
	return indices;
}


void Grid::save( std::ofstream& file )
{

	file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	file << "<map version=\"1.0\" orientation=\"orthogonal\" renderorder=\"right-down\" width=\"" 
		<< mGridWidth << "\" height=\"" << mGridHeight << "\" tilewidth=\"" 
		<< mSquareSize << "\" tileheight=\"" << mSquareSize << "\" nextobjectid=\"1\">\n";
	//file << "<properties>\n"
		//<< "<property name=\"Description\" value=\"Nintendo please don't sue.\"/>\n"
		//<< "<property name=\"name\" value=\"Mario!\"/>\n"
		//<< "</properties>\n";
	file << "<tileset firstgid=\"1\" name=\"spritesheet_ground\" tilewidth=\"32\" tileheight=\"32\" tilecount=\"128\" columns=\"8\">\n"
		<< "<image source=\"spritesheet_ground.png\" width=\"256\" height=\"512\"/>\n"
		<< "</tileset>\n";
	file << "<tileset firstgid=\"129\" name=\"spritesheet_items\" tilewidth=\"32\" tileheight=\"32\" tilecount=\"32\" columns=\"8\">\n"
		<< "<image source=\"spritesheet_items.png\" width=\"256\" height=\"128\"/>\n"
		<< "</tileset>\n";
	file << "<tileset firstgid=\"129\" name=\"spritesheet_tiles\" tilewidth=\"32\" tileheight=\"32\" tilecount=\"128\" columns=\"8\">\n"
		<< "<image source=\"spritesheet_tiles.png\" width=\"256\" height=\"512\"/>\n"
		<< "</tileset>\n";
	file << "<layer name =\"Collision\" width =\"" << mGridWidth << "\" height =\"" << mGridHeight << "\">\n"
		<< "<data encoding=\"csv\">\n";

	/*
	int numSquares = mGridWidth * mGridHeight;
	file << mpValues[0];
	for( int i=1; i<numSquares; i++ )
	{
		file << "," << mpValues[i];
	}*/

	int mapWidth, mapHeight;
	int tileWidth, tileHeight;
	Level* currentLevel = gpGame->getLevel();
	currentLevel->getLevelSize(mapWidth, mapHeight);
	currentLevel->getTileSize(tileWidth, tileHeight);
	mapWidth /= tileWidth;
	mapHeight /= tileHeight;
	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			if (y == mapHeight - 1 && x == mapWidth - 1)
				file << currentLevel->getTile(x, y, "Collision")->getID();
			else
				file << currentLevel->getTile(x, y, "Collision")->getID() << ",";
		}
		file << std::endl;

	}

	file << "</data>\n"
		<< "</layer>\n"
		<< "</map>";

}

void Grid::load( std::ifstream& file )
{
	int numSquares = mGridWidth * mGridHeight;
	for( int i=0; i<numSquares; i++ )
	{
		file >> mpValues[i];
	}
}
