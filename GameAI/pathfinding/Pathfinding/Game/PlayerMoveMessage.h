#ifndef _PLAYERMOVETOMESSAGE_H
#define _PLAYERMOVETOMESSAGE_H

#include "GameMessage.h"
#include "Vector2D.h"
#include "GameApp.h"

class PlayerMoveToMessage : public GameMessage
{
public:
	PlayerMoveToMessage(Vector2D newPos);
	~PlayerMoveToMessage() {}

	void process();

private:
	Vector2D mNewPos;
};

#endif