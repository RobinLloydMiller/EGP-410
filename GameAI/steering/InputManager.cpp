#include "InputManager.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "AddUnitMessage.h"
#include "DeleteUnitMessage.h"

InputManager::InputManager() {}
InputManager::~InputManager() {}

void InputManager::update()
{
	al_get_mouse_state(&mMouseState);
	al_get_keyboard_state(&mKeyState);

	//mouse input
	if (al_mouse_button_down(&mMouseState, 1))//left mouse click
	{
		Vector2D pos(mMouseState.x, mMouseState.y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	//keypresses
	if( al_key_down( &mKeyState, ALLEGRO_KEY_ESCAPE ) )
	{
		GameMessage* pMessage = new ExitGameMessage();
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_A, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new AddUnitMessage(DYNAMIC_ARRIVE, 200, 1, Vector2D(0.0f, 0.0f), 0.0f, 180.0f, 100.0f);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_S, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new AddUnitMessage(DYNAMIC_SEEK, 100, 1, Vector2D(0.0f, 0.0f), 0.0f, 180.0f, 100.0f);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_D, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new DeleteUnitMessage();
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	mPrevKeyState = mKeyState;
}

bool InputManager::keyDown(int key, ALLEGRO_KEYBOARD_STATE& currKeyState, ALLEGRO_KEYBOARD_STATE& prevKeyState)
{
	return (al_key_down(&currKeyState, key) && !al_key_down(&prevKeyState, key));
}