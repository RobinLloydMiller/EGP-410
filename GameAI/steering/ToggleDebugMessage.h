#ifndef _TOGGLEDEBUGMESSAGE_H
#define _TOGGLEDEBUGMESSAGE_H

#include "GameMessage.h"

class ToggleDebugMessage : public GameMessage
{
public:
	ToggleDebugMessage();
	~ToggleDebugMessage();

	void process();
};

#endif