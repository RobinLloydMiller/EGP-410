#include "ChangePropertiesMessage.h"
#include "Game.h"

ChangePropertiesMessage::ChangePropertiesMessage(bool shouldAdd)
:GameMessage(CHANGE_PROPERTIES_MESSAGE), mShouldAdd(shouldAdd)
{
}

ChangePropertiesMessage::~ChangePropertiesMessage()
{
}

void ChangePropertiesMessage::process()
{
	if (gpGame->getKinematicUnitManager()->getUnitCount() == 0 || gpGame->getCurrState() == DEBUG_OFF)
		return;

	int change;
	if (!mShouldAdd)
		change = mChange * -1;
	else
		change = mChange;

	EnemyProperty property = gpGame->getCurrProperty();

	switch (property)
	{
	case MAX_VELOCITY:
		if (gpGame->getEnemyMaxVelocity() + change < 0)
			gpGame->getKinematicUnitManager()->updateMaxVelocity(0);
		else
			gpGame->getKinematicUnitManager()->updateMaxVelocity(gpGame->getEnemyMaxVelocity() + change);
		break;
	case REACTION_RADIUS:
		if (gpGame->getEnemyReactionRadius() + change < 0)
			gpGame->getKinematicUnitManager()->updateReactionRadius(0);
		else
			gpGame->getKinematicUnitManager()->updateReactionRadius(gpGame->getEnemyReactionRadius() + change);
		break;
	case ANGULAR_VELOCITY:
		if (gpGame->getEnemyAngularVelocity() + change < 0)
			gpGame->getKinematicUnitManager()->updateAngularVelocity(0);
		else
			gpGame->getKinematicUnitManager()->updateAngularVelocity(gpGame->getEnemyAngularVelocity() + change);
		break;
	case MAX_ACCELERATION:
		if (gpGame->getEnemyMaxAcceleration() + change < 0)
			gpGame->getKinematicUnitManager()->updateMaxAcceleration(0);
		else
			gpGame->getKinematicUnitManager()->updateMaxAcceleration(gpGame->getEnemyMaxAcceleration() + change);
		break;
	}
}