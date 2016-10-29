#include "SelectPropertiesMessage.h"
#include "Game.h"

SelectPropertiesMessage::SelectPropertiesMessage(EnemyProperty prop)
:GameMessage(SELECT_PROPERTIES_MESSAGE), mProperty(prop)
{
}

SelectPropertiesMessage::~SelectPropertiesMessage()
{
}

//sets property in state manager to the property passed from input manager
void SelectPropertiesMessage::process()
{
	gpGame->setCurrProperty(mProperty);
}