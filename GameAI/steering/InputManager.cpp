#include "InputManager.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "AddUnitMessage.h"
#include "DeleteUnitMessage.h"
#include "ToggleDebugMessage.h"
#include "SelectPropertiesMessage.h"
#include "ChangePropertiesMessage.h"

InputManager::InputManager() {}
InputManager::~InputManager() {}

void InputManager::update()
{
	al_get_mouse_state(&mMouseState);
	al_get_keyboard_state(&mKeyState);

	//mouse input
	/*
	if (al_mouse_button_down(&mMouseState, 1))//left mouse click
	{
		Vector2D pos(mMouseState.x, mMouseState.y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}*/

	//keypresses
	//calling appropriate event for the keypress
	if( al_key_down( &mKeyState, ALLEGRO_KEY_ESCAPE ) )
	{
		GameMessage* pMessage = new ExitGameMessage();
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_D, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new DeleteUnitMessage();
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	/*if (keyDown(ALLEGRO_KEY_S, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new AddUnitMessage(WANDER_AND_SEEK, 100, 1, Vector2D(0.0f, 0.0f), 0.0f, 180.0f, 100.0f);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}
	
	if (keyDown(ALLEGRO_KEY_F, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new AddUnitMessage(WANDER_AND_FLEE, 100, 1, Vector2D(0.0f, 0.0f), 0.0f, 180.0f, 100.0f);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}*/

	if (keyDown(ALLEGRO_KEY_I, mKeyState, mPrevKeyState))
	{
		for (int i = 0; i < 5; ++i)
		{
			GameMessage* pMessage = new AddUnitMessage(BOIDS, Vector2D(300 + (50*i), 300 + (32 * i)), 1, Vector2D(0.0f, 0.0f), 0.0f, 180.0f, 100.0f);
			gpGame->getMessageManager()->addMessage(pMessage, 0);
		}
	}

	if (keyDown(ALLEGRO_KEY_Z, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new ToggleDebugMessage();
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_C, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new SelectPropertiesMessage(COHESION_WEIGHT);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_S, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new SelectPropertiesMessage(SEPERATION_WEIGHT);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_A, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new SelectPropertiesMessage(ALIGNMENT_WEIGHT);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_V, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new SelectPropertiesMessage(MAX_VELOCITY);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_R, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new SelectPropertiesMessage(REACTION_RADIUS);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_O, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new SelectPropertiesMessage(ROTATIONAL_VELOCITY);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_M, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new SelectPropertiesMessage(MAX_ACCELERATION);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_MINUS, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new ChangePropertiesMessage();
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}
	//plus key is holding down shift and pressing the key with = and + on it
	//this is because not all keyboards have a numpad with a dedicated + button
	//but all qwerty keyboards have a plus button there
	if (keyDown(ALLEGRO_KEY_EQUALS, mKeyState, mPrevKeyState) && (al_key_down(&mKeyState, ALLEGRO_KEY_LSHIFT) || al_key_down(&mKeyState, ALLEGRO_KEY_RSHIFT)))
	{
		GameMessage* pMessage = new ChangePropertiesMessage(true);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_S, mKeyState, mPrevKeyState) && (al_key_down(&mKeyState, ALLEGRO_KEY_LCTRL) || al_key_down(&mKeyState, ALLEGRO_KEY_RCTRL)))
	{
		gpGame->getStateManager()->saveData();
	}

	//save previous keystate to have ability to check for key up
	mPrevKeyState = mKeyState;
}

//functions identical to Unity's keyDown function
//checks if key was up last frame and down on current frame
bool InputManager::keyDown(int key, ALLEGRO_KEYBOARD_STATE& currKeyState, ALLEGRO_KEYBOARD_STATE& prevKeyState)
{
	return (al_key_down(&currKeyState, key) && !al_key_down(&prevKeyState, key));
}