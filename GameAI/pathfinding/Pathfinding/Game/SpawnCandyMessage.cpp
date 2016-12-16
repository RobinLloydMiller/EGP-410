#include "SpawnCandyMessage.h"
#include "GameApp.h"

SpawnCandyMessage::SpawnCandyMessage()
:GameMessage(SPAWN_CANDY_MESSAGE)
{
}

void SpawnCandyMessage::process()
{
	gpGameApp->spawnCandy();
}