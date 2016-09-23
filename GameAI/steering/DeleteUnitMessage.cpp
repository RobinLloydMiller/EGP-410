#include "DeleteUnitMessage.h"
#include "Game.h"

DeleteUnitMessage::DeleteUnitMessage()
:GameMessage(DELETE_UNIT_MESSAGE)
{
}

DeleteUnitMessage::DeleteUnitMessage(int index)
:GameMessage(DELETE_UNIT_MESSAGE)
,mIndex(index)
{
}

DeleteUnitMessage::~DeleteUnitMessage()
{
}

void DeleteUnitMessage::process()
{
	if (mIndex == -1)
		gpGame->getKinematicUnitManager()->deleteUnit();
	else
		gpGame->getKinematicUnitManager()->deleteUnit(mIndex);
}