#ifndef _DELETEUNITMESSAGE_H
#define _DELETEUNITMESSAGE_H

#include "GameMessage.h"

class DeleteUnitMessage : public GameMessage
{
public:
	DeleteUnitMessage();
	DeleteUnitMessage(int index);
	~DeleteUnitMessage();

	void process();

private:
	int mIndex = -1;
};

#endif