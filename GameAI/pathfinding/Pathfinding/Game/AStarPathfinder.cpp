#include "AStarPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Grid.h"
#include "GameApp.h"
#include <PerformanceTracker.h>
#include <algorithm>
#include "Vector2D.h"

using namespace std;

AStarPathfinder::AStarPathfinder(Graph* pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
}

AStarPathfinder::~AStarPathfinder()
{
}

const Path& AStarPathfinder::findPath(Node* pFrom, Node* pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it
	list<Node*> nodesToVisit;
	nodesToVisit.push_front(pFrom);

#ifdef VISUALIZE_PATH
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);

	pFrom->setDistToSource(0);

#endif

	clearPath();
	mNodesInPath.clear();

	Node* pCurrentNode = NULL, *pClosest = pFrom;
	bool toNodeAdded = false;


	while (pCurrentNode != pTo && nodesToVisit.size() > 0)
	{
		//get current node from front of list
		pCurrentNode = nodesToVisit.front();
		//remove node from list
		nodesToVisit.pop_front();
		//add Node to Path
		mPath.addNode(pCurrentNode);

		//get the Connections for the current node
		vector<Connection*> connections = mpGraph->getConnections(pCurrentNode->getId());

		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		for (unsigned int i = 0; i<connections.size(); ++i)
		{
			Connection* pConnection = connections[i];
			Node* pTempToNode = connections[i]->getToNode();
			if (!toNodeAdded &&
				!mPath.containsNode(pTempToNode) &&
				find(nodesToVisit.begin(), nodesToVisit.end(), pTempToNode) == nodesToVisit.end())
			{
				//one is always connection weight because we are moving on a grid without diagonals
				if (pCurrentNode->getDistToSource() + 1 < pTempToNode->getDistToSource())
				{
					//add one to the distance of the last node because in a grid all connections are weight one
					pTempToNode->setDistToSource(pCurrentNode->getDistToSource() + 1);
					pTempToNode->setPrevNode(pCurrentNode);
				}

				//ifcurrent is closer to end that shortest push front

				if (getDistance(pTempToNode, pTo) < getDistance(pClosest, pTo))
				{
					pClosest = pTempToNode;
					nodesToVisit.push_front(pClosest);
				}
				else
				{
					nodesToVisit.push_back(pTempToNode);//uncomment me for breadth-first search
				}

				if (pTempToNode == pTo)
				{
					toNodeAdded = true;
				}
#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(pTempToNode);
#endif
			}
		}
	}

	if (pTo->getId() != pFrom->getId())
	{
		//mPath.addNode(pFrom);
		mNodesInPath.push_back(pTo->getId());
		Node* next = pTo->getPrevNode();

		while (next->getId() != pFrom->getId())
		{
			mNodesInPath.push_back(next->getId());
			next = next->getPrevNode();
		}

		mNodesInPath.push_back(pFrom->getId());
	}

	//std::cout << "num nodes " << mPath.getNumNodes() << std::endl;

	for (size_t i = 0; i < mpGraph->getNumNodes(); ++i)
	{
		mpGraph->getNode(i)->setPrevNode(NULL);
		mpGraph->getNode(i)->setDistToSource(std::numeric_limits<double>::infinity());
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	return mPath;

}

void AStarPathfinder::clearPath()
{
	mPath.clear();
}

float AStarPathfinder::getDistance(Node * first, Node * second)
{
	Vector2D firstLoc = gpGameApp->getGrid()->getULCornerOfSquare(first->getId());
	Vector2D secondLoc = gpGameApp->getGrid()->getULCornerOfSquare(second->getId());

	float x = std::pow((firstLoc.getX() - secondLoc.getX()), 2);
	float y = std::pow((firstLoc.getY() - secondLoc.getY()), 2);

	return (float)std::pow((x + y), 0.5);
}

Node* AStarPathfinder::getShortestDistanceNode() const
{
	Node* shortest = mUnvisitedNodes.front();

	for (auto it : mUnvisitedNodes)
	{
		//-1 means distance is unknown
		if (it->getDistToSource() != -1 && shortest->getDistToSource() > it->getDistToSource())
		{
			shortest = it;
		}
	}

	return shortest;
}
