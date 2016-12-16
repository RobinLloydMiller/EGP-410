#ifndef _NOCANDYSTATE_H
#define _NOCANDYSTATE_H

#include "StateMachine.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "SpawnCandyMessage.h"

class NoCandyState : public StateMachineState
{
public:
	NoCandyState(const SM_idType& id) :StateMachineState(id) {}

	virtual void onEntrance() {}
	virtual void onExit() {}
	virtual StateTransition* update() 
	{ 
		if (mGotCandy)
		{

			//find the right transition
			map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(CANDY_TRANSISTION);
			if (iter != mTransitions.end())//found?
			{
				mGotCandy = false;
				StateTransition* pTransition = iter->second;
				return pTransition;
			}
		}
		return NULL; 
	}

	void gotCandy()
	{
		mGotCandy = true;
	}

private:
	bool mGotCandy = false;
};

#endif