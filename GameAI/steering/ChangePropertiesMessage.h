#ifndef _CHANGEPROPERTIESMESSAGE_H
#define _CHANGEPROPERTIESMESSAGE_H

#include "GameMessage.h"

class ChangePropertiesMessage : public GameMessage
{
public:

	ChangePropertiesMessage(bool shouldAdd = false);
	~ChangePropertiesMessage();

	void process();

private:
	int mChange = 10;
	float mWChange = 0.5f;
	bool mShouldAdd;
};

#endif