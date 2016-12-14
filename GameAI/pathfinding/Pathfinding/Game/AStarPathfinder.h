#ifndef _ASTARPATHFINDER_H
#define _ASTARPATHFINDER_H

#include "GridPathfinder.h"
#include <list>

class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class Connection;

class AStarPathfinder : public GridPathfinder
{
public:
	AStarPathfinder(Graph* pGraph);
	~AStarPathfinder();

	const Path& findPath(Node* pFrom, Node* pTo);//make sure to delete the path when you are done!
	virtual void clearPath();

private:
	std::list<Node*> mUnvisitedNodes;
	float getDistance(Node* first, Node* second);

	std::vector<Connection*> getConnections(int x, int y);
	Connection* generateConnection(const int x1, const int y1, const int x2, const int y2);

	Node* getShortestDistanceNode() const;
};

#endif