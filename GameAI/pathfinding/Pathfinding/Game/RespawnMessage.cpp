#include "RespawnMessage.h"
#include "GameApp.h"

RespawnMessage::RespawnMessage()
:GameMessage(RESPAWN_MESSAGE)
{
}

void RespawnMessage::process()
{
	gpGameApp->respawnPlayer();
}