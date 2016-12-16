#ifndef _SPAWNCANDYMESSAGE_H
#define _SPAWNCANDYMESSAGE_H

#include "GameMessage.h"

class SpawnCandyMessage : public GameMessage
{
public:
	SpawnCandyMessage();
	~SpawnCandyMessage() {}

	void process();
};

#endif