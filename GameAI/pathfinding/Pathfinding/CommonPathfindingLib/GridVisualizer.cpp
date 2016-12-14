#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "GridVisualizer.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Grid.h"
#include "Vector2D.h"
#include "Game.h"

GridVisualizer::GridVisualizer( Grid* pGrid )
:mpGrid(pGrid)
,mDirty(true)
{
}

GridVisualizer::~GridVisualizer()
{
}

void GridVisualizer::refresh()
{
	const ALLEGRO_COLOR& color = BLACK_COLOR; 
	const ALLEGRO_COLOR& coinColor = YELLOW_COLOR;
	const ALLEGRO_COLOR& candyColor = BLUE_COLOR;
	const ALLEGRO_COLOR& exitColor = PURPLE_COLOR;
	if( mDirty )
	{
		//remove old entries first
		removeAllEntriesOfColor( color );
		removeAllEntriesOfColor( coinColor );
		removeAllEntriesOfColor( candyColor );
		removeAllEntriesOfColor(exitColor);

		int size = mpGrid->getGridWidth() * mpGrid->getGridHeight();
		//get any non-zero squares and send them to the visualizer
		for( int i=0; i<size; i++ )
		{
			if( mpGrid->getValueAtIndex(i) == 1 )
			{
				addColor( i, color );
			}
			else if (mpGrid->getValueAtIndex(i) == 2)
			{
				addColor(i, coinColor);
			}
			else if (mpGrid->getValueAtIndex(i) == 3)
			{
				addColor(i, candyColor);
			}
			else if (mpGrid->getValueAtIndex(i) == 4)
			{
				addColor(i, exitColor);
			}
		}
	}
	mDirty = false;
}

void GridVisualizer::addColor( int index, const ALLEGRO_COLOR& color )
{
	//set dirty flag
	mDirty = true;

	//find the existing entry in the map (if it exists)
	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter = mColormap.find( color );

	if( iter != mColormap.end() )//found the existing entry
	{
		iter->second.push_back( index );
	}
	else
	{
		//create a vector to put in the map
		std::vector<int> colorVector;
		colorVector.push_back( index );

		//put the vector into the map
		mColormap[color] = colorVector;
	}
}

void GridVisualizer::removeAllEntriesOfColor( const ALLEGRO_COLOR& color )
{
	//find the existing entry in the map (if it exists)
	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter = mColormap.find( color );
	
	if( iter != mColormap.end() )
	{
		mColormap.erase( iter );
	}
}

void GridVisualizer::draw( GraphicsBuffer& dest )
{
	if( mDirty )
	{
		refresh();
	}

	ALLEGRO_BITMAP* pOldTarget = GraphicsSystem::switchTargetBitmap( dest.getBitmap() );

	int gridHeight = mpGrid->getGridHeight();
	int gridWidth = mpGrid->getGridWidth();
	int numSquares = gridWidth * gridHeight;
	int squareSize = mpGrid->getSquareSize();

	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter;
	for( iter = mColormap.begin(); iter != mColormap.end(); ++iter )
	{
		std::vector<int> theIndices = iter->second;

		for( unsigned int i=0; i<theIndices.size(); ++i )
		{
			Vector2D ulPos = mpGrid->getULCornerOfSquare( theIndices[i] );
			al_draw_filled_rectangle( ulPos.getX(), ulPos.getY(), ulPos.getX() + squareSize, ulPos.getY() + squareSize, iter->first );

			char* text = "";
			if (iter->first.r == mStartColor.r && iter->first.g == mStartColor.g && iter->first.b == mStartColor.b)
				text = "S";
			else if (iter->first.r == mStopColor.r && iter->first.g == mStopColor.g && iter->first.b == mStopColor.b)
				text = "G";
			al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), ulPos.getX(), ulPos.getY(), ALLEGRO_ALIGN_LEFT, text);

			//mpBuffer->fillRegion( ulPos, Vector2D( ulPos.getX() + squareSize, ulPos.getY() + squareSize ), iter->first );
		}
	}
}

void GridVisualizer::drawPath(GraphicsBuffer & dest, std::vector<int>& nodesInPath)
{
	ALLEGRO_BITMAP* pOldTarget = GraphicsSystem::switchTargetBitmap(dest.getBitmap());

	for (size_t i = 0; i < nodesInPath.size(); ++i)
	{
		Vector2D one = mpGrid->getULCornerOfSquare(nodesInPath[i]);
		Vector2D two = mpGrid->getULCornerOfSquare(nodesInPath[i + 1]);

		al_draw_line(one.getX() + mpGrid->getSquareSize() / 2, one.getY() + mpGrid->getSquareSize() / 2,
			two.getX() + mpGrid->getSquareSize() / 2, two.getY() + mpGrid->getSquareSize() / 2,
			al_map_rgb(255, 255, 255), 5.0f);

		//std::cout << "line drawn\n";

		if (i + 1 >= nodesInPath.size() - 1)
			break;
	}
}

void GridVisualizer::flipBuffer(GraphicsBuffer & dest)
{
	GraphicsSystem::switchTargetBitmap(dest.getBitmap());
}

void GridVisualizer::clear()
{
	mColormap.clear();
}