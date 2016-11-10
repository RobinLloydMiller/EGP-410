#include "DijkstraPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <algorithm>

using namespace std;

DijkstraPathfinder::DijkstraPathfinder(Graph* pGraph)
:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
}

DijkstraPathfinder::~DijkstraPathfinder()
{
}

const Path& DijkstraPathfinder::findPath(Node* pFrom, Node* pTo)
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

	/*pFrom->setDistToSource(0);
	mUnvisitedNodes.push_front(pFrom);

	for (size_t i = 0; i < mpGraph->getNumNodes(); ++i)
	{
		Node* tmpNode = mpGraph->getNode(i);

		if (tmpNode->getId() != pFrom->getId())
			mUnvisitedNodes.push_front(tmpNode);
	}*/

#endif

	clearPath();

	/*while (!mUnvisitedNodes.empty())
	{
		Node* shortest = getShortestDistanceNode();
		mUnvisitedNodes.remove(shortest);

		vector<Connection*> connections = mpGraph->getConnections(shortest->getId());
		for (auto it : connections)
		{
			Node* toNode = it->getToNode();

			float alt = shortest->getDistToSource() + 1;
			if (toNode->getDistToSource() == -1)
				toNode->setDistToSource(alt);

			if (alt < toNode->getDistToSource())
			{
				toNode->setPrevNode(shortest);
			}
		}
	}

	std::cout << std::endl << (bool)(pFrom->getPrevNode() == NULL);*/

	/*Node* next = pFrom->getPrevNode();
	mPath.addNode(pFrom);

	while (!mPath.containsNode(pTo))
	{
		mPath.addNode(next);
		next = next->getPrevNode();
	}*/


	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;
	

	while (pCurrentNode != pTo && nodesToVisit.size() > 0)
	{
		//get current node from front of list
		pCurrentNode = nodesToVisit.front();
		//remove node from list
		nodesToVisit.pop_front();
		//add Node to Path
		//mPath.addNode(pCurrentNode);

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
				//nodesToVisit.push_front( pTempToNode );//uncomment me for depth-first search
				nodesToVisit.push_back(pTempToNode);//uncomment me for breadth-first search

				double alt = pCurrentNode->getDistToSource() + 1;
				if (alt < pTempToNode->getDistToSource())
				{
					pTempToNode->setDistToSource(alt);
					pCurrentNode->setPrevNode(pTempToNode);
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

	Node* next = pTo;
	mPath.addNode(next);

	if (pTo->getId() != pFrom->getId())
	{
		std::cout << std::endl << (pFrom->getPrevNode()->getPrevNode()->getPrevNode()->getPrevNode() == NULL);

		//while (true)
		//{
			//mPath.addNode(next->getPrevNode());
			//mPath.addNode(next->getPrevNode()->getPrevNode());
		//}
	}

	std::cout << "num nodes " << mPath.getNumNodes() << std::endl;

	for (size_t i = 0; i < mpGraph->getNumNodes(); ++i)
	{
		mpGraph->getNode(i)->setPrevNode(NULL);
		mpGraph->getNode(i)->setDistToSource(std::numeric_limits<double>::infinity());
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	return mPath;

}

void DijkstraPathfinder::clearPath()
{
	mPath.clear();
}

Node* DijkstraPathfinder::getShortestDistanceNode() const
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
