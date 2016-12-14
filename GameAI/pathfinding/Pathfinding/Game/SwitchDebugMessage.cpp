#include "SwitchDebugMessage.h"
#include "GameApp.h"

SwitchDebugMessage::SwitchDebugMessage(bool drawDebug)
:GameMessage(SWITCH_DEBUG_MESSAGE)
,mDrawDebug(drawDebug)
{
}

void SwitchDebugMessage::process()
{
	gpGameApp->setDrawDebugLine(mDrawDebug);
}