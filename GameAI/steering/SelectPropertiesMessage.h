#ifndef _SELECTPROPERTIESMESSAGE_H
#define _SELECTPROPERTIESMESSAGE_H

#include "GameMessage.h"
#include "StateManager.h"

class SelectPropertiesMessage : public GameMessage
{
public:
	SelectPropertiesMessage(EnemyProperty prop);
	~SelectPropertiesMessage();

	void process();

private:
	EnemyProperty mProperty;
};

#endif