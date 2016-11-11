#include "ExitGameMessage.h"
#include "GameApp.h"

ExitGameMessage::ExitGameMessage()
	:GameMessage(EXIT_GAME_MESSAGE)
{
}

void ExitGameMessage::process()
{
	gpGameApp->markForExit();
}