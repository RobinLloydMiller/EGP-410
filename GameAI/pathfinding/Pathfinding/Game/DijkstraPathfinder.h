#ifndef _DIJKSTRAPATHFINDER_H
#define _DIJKSTRAPATHFINDER_H

#include "GridPathfinder.h"
#include <vector>
#include <list>


class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class DijkstraPathfinder :public GridPathfinder
{
public:
	DijkstraPathfinder(Graph* pGraph);
	~DijkstraPathfinder();

	const Path& findPath(Node* pFrom, Node* pTo);//make sure to delete the path when you are done!
	virtual void clearPath();

private:
	std::list<Node*> mUnvisitedNodes;

	Node* getShortestDistanceNode() const;
};

#endif