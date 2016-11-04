#ifndef _PATHFINDINGDEBUGCONTENT_H
#define _PATHFINDINGDEBUGCONTENT_H

#include "DebugContent.h"

class GridPathfinder;

class PathfindingDebugContent:public DebugContent
{
public:
	PathfindingDebugContent( GridPathfinder* pPathfinder );
	~PathfindingDebugContent(){};

	std::string getDebugString();

private:
	GridPathfinder* mpPathfinder;
};

#endif