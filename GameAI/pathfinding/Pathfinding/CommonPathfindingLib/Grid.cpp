#include "Grid.h"
#include "GraphicsSystem.h"
#include "Vector2D.h"
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
	int index = getValueAtPixelXY(x, y);
	int index2 = getValueAtPixelXY(x + mSquareSize - 1, y);
	int index3 = getValueAtPixelXY(x, y + mSquareSize - 1);
	int index4 = getValueAtPixelXY(x + mSquareSize - 1, y + mSquareSize - 1);

	if (index == value)
		return Vector2D(x, y);
	if (index2 == value)
		return Vector2D(x + mSquareSize - 1, y);
	if (index3 == value)
		return Vector2D(x, y + mSquareSize - 1);
	if (index4 == value)
		return Vector2D(x + mSquareSize - 1, y + mSquareSize - 1);

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
	int numSquares = mGridWidth * mGridHeight;
	for( int i=0; i<numSquares; i++ )
	{
		file << mpValues[i] << " ";
	}
}

void Grid::load( std::ifstream& file )
{
	int numSquares = mGridWidth * mGridHeight;
	for( int i=0; i<numSquares; i++ )
	{
		file >> mpValues[i];
	}
}
