#ifndef SWITCHPATHFINDINGMESSAGE_H
#define SWITCHPATHFINDINGMESSAGE_H

#include "GameMessage.h"

enum class PathfinderType;

class SwitchPathfindingMessage : public GameMessage
{
public: 
	SwitchPathfindingMessage(PathfinderType newPathfinderType);
	~SwitchPathfindingMessage() {}

	void process();

private:
	PathfinderType mPathfinderType;
};

#endif
