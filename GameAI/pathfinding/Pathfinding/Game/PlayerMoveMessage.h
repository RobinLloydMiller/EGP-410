#ifndef _PLAYERMOVEMESSAGE_H
#define _PLAYERMOVEMESSAGE_H

#include "GameMessage.h"
#include "GameApp.h"

class PlayerMoveToMessage : public GameMessage
{
public:
	PlayerMoveToMessage(PlayerDirection dir);
	~PlayerMoveToMessage() {}

	void process();

private:
	PlayerDirection mDir;
};

#endif