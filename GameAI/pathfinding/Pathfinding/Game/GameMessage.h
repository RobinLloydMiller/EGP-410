#ifndef _GAMEMESSAGE_H
#define _GAMEMESSAGE_H

#include <Trackable.h>

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	PATH_TO_MESSAGE = 1,
	SWITCH_PATHFINDING_MESSAGE = 2,
	EXIT_GAME_MESSAGE = 3,
	PLAYER_MOVE_TO_MESSAGE = 4
};

class GameMessage: public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage( MessageType type  );
	~GameMessage();

	double getSubmittedTime() const { return mSubmittedTime; };
	double getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	double mSubmittedTime;
	double mScheduledTime;

private:
	virtual void process() = 0; 
};

#endif