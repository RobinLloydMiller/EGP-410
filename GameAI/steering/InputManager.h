#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include "Defines.h"
#include <Vector2D.h>
#include "PlayerMoveToMessage.h"
#include "ExitGameMessage.h"
#include <allegro5/allegro.h>
#include <sstream>

class InputManager
{
public:
	InputManager();
	~InputManager();
	void update();

	//getters
	float getMouseX() { return mMouseState.x; }
	float getMouseY() { return mMouseState.y; }
	std::string getMousePosString() {
		std::stringstream mousePos;
		mousePos << mMouseState.x << ":" << mMouseState.y;
		return mousePos.str(); }

private:
	ALLEGRO_MOUSE_STATE mMouseState;
	ALLEGRO_KEYBOARD_STATE mKeyState;
	ALLEGRO_KEYBOARD_STATE mPrevKeyState;

	//returns true if key was pressed this frame, false if it was held down since last frame
	bool keyDown(int key, ALLEGRO_KEYBOARD_STATE& currKeyState, ALLEGRO_KEYBOARD_STATE& prevKeyState);
};

#endif