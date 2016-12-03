#include "PlayerMoveMessage.h"
#include "Grid.h"

PlayerMoveToMessage::PlayerMoveToMessage(PlayerDirection dir)
:GameMessage(PLAYER_MOVE_MESSAGE)
,mDir(dir)
{
}

void PlayerMoveToMessage::process()
{
	gpGameApp->setPlayerDir(mDir);
}