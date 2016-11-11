#include "SwitchPathfindingMessage.h"
#include "GameApp.h"

SwitchPathfindingMessage::SwitchPathfindingMessage(PathfinderType newPathfinderType)
	:GameMessage(SWITCH_PATHFINDING_MESSAGE), mPathfinderType(newPathfinderType)
{
}

void SwitchPathfindingMessage::process()
{
	gpGameApp->switchPathfinding(mPathfinderType);

	switch (mPathfinderType)
	{
	case PathfinderType::DIJKSTRA:
		std::cout << "Switched Pathfinding to Dijkstra" << std::endl;
		break;
	case PathfinderType::ASTAR:
		std::cout << "Switched Pathfinding to A*" << std::endl;
		break;
	default:
		break;
	}
}