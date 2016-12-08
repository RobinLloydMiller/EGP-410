#ifndef _PLAYERMOVEMESSAGE_H
#define _PLAYERMOVEMESSAGE_H

#include "GameMessage.h"
#include "GameApp.h"

class PlayerMoveToMessage : public GameMessage
{
public:
	PlayerMoveToMessage(Direction dir);
	~PlayerMoveToMessage() {}

	void process();

private:
	Direction mDir;
};

#endif