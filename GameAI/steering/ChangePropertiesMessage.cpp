#include "ChangePropertiesMessage.h"
#include "Game.h"

ChangePropertiesMessage::ChangePropertiesMessage(bool shouldAdd)
:GameMessage(CHANGE_PROPERTIES_MESSAGE), mShouldAdd(shouldAdd)
{
}

ChangePropertiesMessage::~ChangePropertiesMessage()
{
}

//modifies value of currently selected property in state manager
//bool mShouldAdd denotes whether to add or subtract from value
void ChangePropertiesMessage::process()
{
	if (gpGame->getKinematicUnitManager()->getUnitCount() == 0 || gpGame->getCurrState() == DEBUG_OFF)
		return;

	int change;
	float wChange;
	if (!mShouldAdd)
	{
		change = mChange * -1;
		wChange = mWChange * -1;
	}
	else
	{
		change = mChange;
		wChange = mWChange;
	}

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
	case ROTATIONAL_VELOCITY:
		if (gpGame->getEnemyMaxRotationalVelocity() + change < 0)
			gpGame->getKinematicUnitManager()->updateMaxRotationalVelocity(0);
		else
			gpGame->getKinematicUnitManager()->updateMaxRotationalVelocity(gpGame->getEnemyMaxRotationalVelocity() + change);
		break;
	case MAX_ACCELERATION:
		if (gpGame->getEnemyMaxAcceleration() + change < 0)
			gpGame->getKinematicUnitManager()->updateMaxAcceleration(0);
		else
			gpGame->getKinematicUnitManager()->updateMaxAcceleration(gpGame->getEnemyMaxAcceleration() + change);
		break;
	case ALIGNMENT_WEIGHT:
		if (gpGame->getStateManager()->getAlignmentWeight() + wChange < 0)
			gpGame->getStateManager()->setAlignmentWeight(0);
		else
			gpGame->getStateManager()->setAlignmentWeight(gpGame->getStateManager()->getAlignmentWeight() + wChange);
		break;		
	case COHESION_WEIGHT:
		if (gpGame->getStateManager()->getCohesionWeight() + wChange < 0)
			gpGame->getStateManager()->setCohesionWeight(0);
		else
			gpGame->getStateManager()->setCohesionWeight(gpGame->getStateManager()->getCohesionWeight() + wChange);
		break;
	case SEPERATION_WEIGHT:
		if (gpGame->getStateManager()->getSeperationWeight() + wChange < 0)
			gpGame->getStateManager()->setSeperationWeight(0);
		else
			gpGame->getStateManager()->setSeperationWeight(gpGame->getStateManager()->getSeperationWeight() + wChange);
		break;
	}
}