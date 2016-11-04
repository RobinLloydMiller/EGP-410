#ifndef _DEBUGCONTENT_H
#define _DEBUGCONTENT_H

#include <string>
#include <Trackable.h>

class DebugContent:public Trackable
{
public:
	DebugContent(){};
	virtual ~DebugContent(){};

	virtual std::string getDebugString() = 0;
};

#endif