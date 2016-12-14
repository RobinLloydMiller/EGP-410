#include "PathToMessage.h"
#include "Game.h"
#include "GameApp.h"
#include "GridPathfinder.h"
#include "Grid.h"
#include "GridGraph.h"

PathToMessage::PathToMessage( const Vector2D& from, const Vector2D& to, GridPathfinder* pathfinder )
:GameMessage(PATH_TO_MESSAGE)
,mFrom(from)
,mTo(to)
,mpPathfinder(pathfinder)
{
}

PathToMessage::~PathToMessage()
{
}

void PathToMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	if( pGame != NULL ) 
	{
		if(mpPathfinder == nullptr)
			mpPathfinder = pGame->getPathfinder();
		GridGraph* pGridGraph = pGame->getGridGraph();
		Grid* pGrid = pGame->getGrid();
		int fromIndex = pGrid->getSquareIndexFromPixelXY( (int)mFrom.getX(), (int)mFrom.getY() );
		int toIndex = pGrid->getSquareIndexFromPixelXY( (int)mTo.getX(), (int)mTo.getY() );
		Node* pFromNode = pGridGraph->getNode( fromIndex );
		Node* pToNode = pGridGraph->getNode( toIndex );
		if (pFromNode != NULL && pToNode != NULL)
		{
			mpPathfinder->findPath(pFromNode, pToNode);
		}
	}
}
