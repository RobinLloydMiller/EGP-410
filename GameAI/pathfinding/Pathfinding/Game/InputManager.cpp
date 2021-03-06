#include "InputManager.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "Vector2D.h"
#include "PathToMessage.h"
#include "GridPathfinder.h"
#include "SwitchPathfindingMessage.h"
#include "ExitGameMessage.h"
#include "PlayerMoveMessage.h"
#include "SwitchDebugMessage.h"
#include "SetPlayerInvincibleMessage.h"

InputManager::InputManager() {

}
InputManager::~InputManager() {}

void InputManager::update()
{
	al_get_mouse_state(&mMouseState);
	al_get_keyboard_state(&mKeyState);

	Vector2D playerPos = gpGameApp->getPlayerPos();

	//mouse input
	/*
	if (mouseDown(1, mMouseState, mPrevMouseState))
	{
		static Vector2D lastPos(0.0f, 0.0f);
		if (mStartSelect)
		{
			gpGameApp->getPathfinder()->clearPath();
			lastPos = Vector2D(mMouseState.x, mMouseState.y);

			//find path to itself to draw the start node
			GameMessage* pMessage = new PathToMessage(lastPos, lastPos);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);

			mStartSelect = false;
		}

		else
		{
			Vector2D pos(mMouseState.x, mMouseState.y);
			GameMessage* pMessage = new PathToMessage(lastPos, pos);
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
			mStartSelect = true;
		}
	}*/

	//keypresses
	//calling appropriate event for the keypress
	if (al_key_down(&mKeyState, ALLEGRO_KEY_ESCAPE))
	{
		GameMessage* pMessage = new ExitGameMessage();
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_A, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new SwitchPathfindingMessage(PathfinderType::ASTAR);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_D, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new SwitchPathfindingMessage(PathfinderType::DIJKSTRA);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_L, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new SwitchDebugMessage(true);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_K, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new SwitchDebugMessage(false);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_I, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new SetPlayerInvincibleMessage(true);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_U, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new SetPlayerInvincibleMessage(false);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_F, mKeyState, mPrevKeyState))
	{
		gpGameApp->changeGrid(0);
	}
	if (keyDown(ALLEGRO_KEY_G, mKeyState, mPrevKeyState))
	{
		gpGameApp->changeGrid(1);
	}

	if (keyDown(ALLEGRO_KEY_DOWN, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new PlayerMoveToMessage(Direction::DOWN);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_UP, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new PlayerMoveToMessage(Direction::UP);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_LEFT, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new PlayerMoveToMessage(Direction::LEFT);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}

	if (keyDown(ALLEGRO_KEY_RIGHT, mKeyState, mPrevKeyState))
	{
		GameMessage* pMessage = new PlayerMoveToMessage(Direction::RIGHT);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}


	if (keyDown(ALLEGRO_KEY_H, mKeyState, mPrevKeyState))
	{
		gpGameApp->toggleHelp();
	}

	//save previous keystate to have ability to check for key up
	mPrevKeyState = mKeyState;
	mPrevMouseState = mMouseState;
}

//functions identical to Unity's keyDown function
//checks if key was up last frame and down on current frame
bool InputManager::keyDown(int key, ALLEGRO_KEYBOARD_STATE& currKeyState, ALLEGRO_KEYBOARD_STATE& prevKeyState)
{
	return (al_key_down(&currKeyState, key) && !al_key_down(&prevKeyState, key));
}

bool InputManager::mouseDown(int button, ALLEGRO_MOUSE_STATE & currMouseState, ALLEGRO_MOUSE_STATE & prevMouseState)
{
	return (al_mouse_button_down(&currMouseState, button) && !al_mouse_button_down(&prevMouseState, button));
}