#ifndef _GRIDPATHFINDER_H
#define _GRIDPATHFINDER_H

#include "Pathfinder.h"

class GridGraph;
class GridVisualizer;
class GraphicsBuffer;
class PathfindingDebugContent;

class GridPathfinder:public Pathfinder
{
public:
	friend class PathfindingDebugContent;

	GridPathfinder( GridGraph* pGraph );
	virtual ~GridPathfinder();

	virtual const Path& findPath( Node* pFrom, Node* pTo ) = 0;
	virtual void clearPath() = 0;
	
#ifdef VISUALIZE_PATH
	//just for visualization
public:
	void drawVisualization( Grid* pGrid, GraphicsBuffer* pDest );
	std::vector<int> getNodesInPath() { return mNodesInPath; }
protected:
	std::vector<Node*> mVisitedNodes;
	GridVisualizer* mpVisualizer;
	//added this to be the real shorest path, nodes in here will be have a line drawn to connect them all
	std::vector<int> mNodesInPath;

#endif

	double mTimeElapsed;
};

#endif