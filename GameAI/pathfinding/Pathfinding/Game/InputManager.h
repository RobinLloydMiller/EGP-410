#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include "Trackable.h"
#include <allegro5/allegro.h>
#include <sstream>

class InputManager : public Trackable
{
public:
	InputManager();
	~InputManager();
	void update();

	//getters
	float getMouseX() const { return mMouseState.x; }
	float getMouseY() const { return mMouseState.y; }
	std::string getMousePosString() {
		std::stringstream mousePos;
		mousePos << mMouseState.x << ":" << mMouseState.y;
		return mousePos.str();
	}

private:
	ALLEGRO_MOUSE_STATE mMouseState;
	ALLEGRO_MOUSE_STATE mPrevMouseState;
	ALLEGRO_KEYBOARD_STATE mKeyState;
	ALLEGRO_KEYBOARD_STATE mPrevKeyState;

	//bool to tell whether or not to place the start or ened node
	bool mStartSelect = true;

	//returns true if key was pressed this frame, false if it was held down since last frame
	bool keyDown(int key, ALLEGRO_KEYBOARD_STATE& currKeyState, ALLEGRO_KEYBOARD_STATE& prevKeyState);
	//like the keydown function but for mouse presses so you dont get continuous input
	bool mouseDown(int button, ALLEGRO_MOUSE_STATE& currMouseState, ALLEGRO_MOUSE_STATE& prevMouseState);
};

#endif