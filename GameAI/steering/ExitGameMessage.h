#ifndef _EXITGAMEMESSAGE_H
#define _EXITGAMEMESSAGE_H

#include "GameMessage.h"

class ExitGameMessage : public GameMessage
{
public:
	ExitGameMessage();
	~ExitGameMessage();

	void process();
};

#endif