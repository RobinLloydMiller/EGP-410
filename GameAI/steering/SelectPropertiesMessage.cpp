#include "SelectPropertiesMessage.h"
#include "Game.h"

SelectPropertiesMessage::SelectPropertiesMessage(EnemyProperty prop)
:GameMessage(SELECT_PROPERTIES_MESSAGE), mProperty(prop)
{
}

SelectPropertiesMessage::~SelectPropertiesMessage()
{
}

void SelectPropertiesMessage::process()
{
	gpGame->setCurrProperty(mProperty);
}