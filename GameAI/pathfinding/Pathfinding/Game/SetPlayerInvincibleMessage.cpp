#include "SetPlayerInvincibleMessage.h"
#include "GameApp.h"

SetPlayerInvincibleMessage::SetPlayerInvincibleMessage(bool invincible)
:GameMessage(SET_PLAYER_INVINCIBLE_MESSAGE)
,mInvincible(invincible)
{
}

void SetPlayerInvincibleMessage::process()
{
	gpGameApp->setPlayerInvincible(mInvincible);
}