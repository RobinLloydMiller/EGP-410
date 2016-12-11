#ifndef _SETPLAYERINVINCILBEMESSAGE_H
#define _SETPLAYERINVINCILBEMESSAGE_H

#include "GameMessage.h"

class SetPlayerInvincibleMessage : public GameMessage
{
public:
	SetPlayerInvincibleMessage(bool invincible);
	~SetPlayerInvincibleMessage() {}

	void process();
private:
	bool mInvincible;
};

#endif
