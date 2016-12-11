#ifndef _CANDYSTATE_H
#define _CANDYSTATE_h

#include "StateMachine.h"
#include <map>

class CandyState : public StateMachineState
{
public:
	CandyState(const SM_idType& id) :StateMachineState(id) {}

	virtual void onEntrance() { mTimeToStop = 1000.0f; }
	virtual void onExit() { mTimeToStop = 0.0f; }
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
