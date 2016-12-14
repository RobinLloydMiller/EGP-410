#ifndef _RESPAWNMESSAGE_H
#define _RESPAWNMESSAGE_H

#include "GameMessage.h"

class RespawnMessage : public GameMessage
{
public:
	RespawnMessage();
	~RespawnMessage() {}

	void process();

private:
	
};

#endif