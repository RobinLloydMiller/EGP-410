#ifndef _CANDYSTATE_H
#define _CANDYSTATE_h

#include "StateMachine.h"
#include "GameApp.h"
#include "Player.h"
#include <map>

class CandyState : public StateMachineState
{
public:
	CandyState(const SM_idType& id) :StateMachineState(id) {}

	virtual void onEntrance() 
	{ 
		mTimeToStop = 3000.0f; gpGameApp->flee(); 

		GameMessage* pMessage = new SpawnCandyMessage();
		//wait 60 seconds before spawning new candy
		gpGameApp->getMessageManager()->addMessage(pMessage, 60000);
		gpGameApp->getPlayer()->candyColor();
	}
	virtual void onExit() { mTimeToStop = 0.0f; gpGameApp->findAPath(); gpGameApp->getPlayer()->noCandyColor(); }
	virtual StateTransition* update()
	{
		if (mTimeToStop > 0)
		{
			mTimeToStop -= gpGameApp->getLoopTime();
		}

		if (mTimeToStop < 0)
		{
			//find the right transition
			map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(NO_CANDY_TRANSISTION);
			if (iter != mTransitions.end())//found?
			{
				mTimeToStop = 0.0f;
				StateTransition* pTransition = iter->second;
				return pTransition;
			}
		}
		return NULL;
	}

private:
	float mTimeToStop = 0.0f;
};

#endif
