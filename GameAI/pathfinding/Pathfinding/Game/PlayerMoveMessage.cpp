#include "PlayerMoveMessage.h"

PlayerMoveToMessage::PlayerMoveToMessage(Vector2D newPos)
:GameMessage(PLAYER_MOVE_TO_MESSAGE)
,mNewPos(newPos)
{
}

void PlayerMoveToMessage::process()
{
	gpGameApp->setPlayerPos(mNewPos);
}