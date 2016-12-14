#ifndef _SWITCHDEBUGMESSAGE_H
#define _SWITCHDEBUGMESSAGE_H

#include "GameMessage.h"

class SwitchDebugMessage : public GameMessage
{
public:
	SwitchDebugMessage(bool drawDebug);
	~SwitchDebugMessage() {}

	void process();

private:
	bool mDrawDebug;
};

#endif
