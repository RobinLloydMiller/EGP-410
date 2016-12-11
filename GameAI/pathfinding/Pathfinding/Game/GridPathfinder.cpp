#include <allegro5/allegro.h>
#include "GridPathfinder.h"
#include "GridGraph.h"
#include "GridVisualizer.h"
#include "Path.h"
#include "GameApp.h"
#include "GraphicsBuffer.h"

GridPathfinder::GridPathfinder( GridGraph* pGraph )
:Pathfinder(pGraph)
,mTimeElapsed(0.0)
{
#ifdef VISUALIZE_PATH
	mpVisualizer = NULL;
#endif
}

GridPathfinder::~GridPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpVisualizer;
#endif
}

#ifdef VISUALIZE_PATH
void GridPathfinder::drawVisualization( Grid* pGrid, GraphicsBuffer* pDest, bool lineOnly )
{
	if (mpVisualizer == NULL)
	{
		mpVisualizer = new GridVisualizer(pGrid);
	}
	else
	{
		mpVisualizer->clear();
	}

	//only gonna draw the line for this project

	/*static ALLEGRO_COLOR pathColor = al_map_rgb(33, 137, 43);

	switch (gpGameApp->getPathfindingType())
	{
	case PathfinderType::ASTAR:
		pathColor = al_map_rgb(4, 75, 201);
		break;
	case PathfinderType::DIJKSTRA:
		pathColor = al_map_rgb(239, 31, 31);
		break;
	}


	static ALLEGRO_COLOR startColor = al_map_rgb(1, 255, 128);
	static ALLEGRO_COLOR stopColor = al_map_rgb(1, 128, 255);

	unsigned int numNodes = mPath.getNumNodes();
	ALLEGRO_COLOR currentPathColor = pathColor;

	if (numNodes > 0)
	{
		for (unsigned int i = 1; i < numNodes-1; i++)
		{
			mpVisualizer->addColor(mPath.peekNode(i)->getId(), currentPathColor);
			float lerpVal = lerp( i, 0, numNodes );
			currentPathColor.r = 1.0f - lerpVal;
		}

		//add beginning and ending color
		mpVisualizer->addColor(mPath.peekNode(0)->getId(), startColor);
		mpVisualizer->addColor(mPath.peekNode(numNodes - 1)->getId(), stopColor);
	}*/

	//mpVisualizer->draw(*pDest);
	if(lineOnly)
		mpVisualizer->drawPath(*pDest, mNodesInPath);
}
#endif