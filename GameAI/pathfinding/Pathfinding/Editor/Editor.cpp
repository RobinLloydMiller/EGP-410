#include <fstream>
#include <allegro5/allegro_primitives.h>

#include "Game.h"
#include "Editor.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Grid.h"
#include "GridVisualizer.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Vector2D.h"

#include "Level.h"

using namespace std;

const int GRID_SQUARE_SIZE = 32;
const IDType BACKGROUND_ID = ENDING_SEQUENTIAL_ID + 1;

Editor::Editor()
:Game()
,mpGrid(NULL)
,mpGridVisualizer(NULL)
{
}

Editor::~Editor()
{
	cleanup();
}

bool Editor::init()
{
	bool retVal = Game::init();
	if( retVal == false )
	{

		return false;
	}

	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);

	mpGridVisualizer = new GridVisualizer( mpGrid );

	//load buffers
	mpGraphicsBufferManager->loadBuffer( BACKGROUND_ID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( BACKGROUND_ID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
	}

	mpHelpMenuBuffer = new GraphicsBuffer("../assets/EditorHelp.png");
	mpHelpMenu = new Sprite(mpHelpMenuBuffer, 0, 0, 1024, 768);
	mDrawHelp = false;

	mLevels.push_back(new Level("../assets/Level1.tmx", "../assets/Level1.txt"));
	mLevels.push_back(new Level("../assets/Level2.tmx", "../assets/Level2.txt"));
	mLevels.push_back(new Level("../assets/Level3.tmx", "../assets/Level3.txt"));
	mLevels.push_back(new Level("../assets/Level4.tmx", "../assets/Level4.txt"));
	mLevels[0]->getTileSize(mTileHeight, mTileWidth);

	al_get_mouse_state(&mMouseState);
	al_get_keyboard_state(&mKeyboardState);
	al_get_keyboard_state(&mPrevKeyboardState);

	mpMasterTimer->start();
	return true;
}

void Editor::cleanup()
{
	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGrid;
	mpGrid = NULL;

	delete mpHelpMenuBuffer;
	mpHelpMenuBuffer = NULL;

	delete mpHelpMenu;
	mpHelpMenu = NULL;

	for (size_t i = 0; i < mLevels.size(); ++i)
	{
		delete mLevels[i];
		mLevels[i] = NULL;
	}
}

void Editor::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void Editor::processLoop()
{
	mPrevKeyboardState = mKeyboardState;

	al_get_mouse_state(&mMouseState);
	al_get_keyboard_state(&mKeyboardState);

	if (al_mouse_button_down(&mMouseState, 1))//left mouse click
	{
		mLevels[mCurrentLevel]->getTile(mMouseState.x / mTileWidth, mMouseState.y / mTileHeight, "Collision")->setID(1);

		//mpGrid->setValueAtPixelXY( mMouseState.x, mMouseState.y, BLOCKING_VALUE );
		//mpGridVisualizer->setModified();
	}
	else if (al_mouse_button_down(&mMouseState, 2))//right mouse down
	{
		mLevels[mCurrentLevel]->getTile(mMouseState.x / mTileWidth, mMouseState.y / mTileHeight, "Collision")->setID(0);

		//mpGrid->setValueAtPixelXY( mMouseState.x, mMouseState.y, CLEAR_VALUE );
		//mpGridVisualizer->setModified();
	}

	if (keyDown(ALLEGRO_KEY_1, mKeyboardState, mPrevKeyboardState))
	{
		mLevels[mCurrentLevel]->getTile(mMouseState.x / mTileWidth, mMouseState.y / mTileHeight, "Collision")->setID(138);
	}
	else if (keyDown(ALLEGRO_KEY_2, mKeyboardState, mPrevKeyboardState))
	{
		mLevels[mCurrentLevel]->getTile(mMouseState.x / mTileWidth, mMouseState.y / mTileHeight, "Collision")->setID(155);
	}
	else if (keyDown(ALLEGRO_KEY_3, mKeyboardState, mPrevKeyboardState))
	{
		mLevels[mCurrentLevel]->getTile(mMouseState.x / mTileWidth, mMouseState.y / mTileHeight, "Collision")->setID(131);
	}
	else if (keyDown(ALLEGRO_KEY_4, mKeyboardState, mPrevKeyboardState))
	{
		mLevels[mCurrentLevel]->getTile(mMouseState.x / mTileWidth, mMouseState.y / mTileHeight, "Collision")->setID(145);
	}
	else if (keyDown(ALLEGRO_KEY_5, mKeyboardState, mPrevKeyboardState))
	{
		mLevels[mCurrentLevel]->getTile(mMouseState.x / mTileWidth, mMouseState.y / mTileHeight, "Collision")->setID(140);
	}
	else if (keyDown(ALLEGRO_KEY_6, mKeyboardState, mPrevKeyboardState))
	{
		mLevels[mCurrentLevel]->getTile(mMouseState.x / mTileWidth, mMouseState.y / mTileHeight, "Collision")->setID(268);
	}
	else if (keyDown(ALLEGRO_KEY_7, mKeyboardState, mPrevKeyboardState))
	{
		mLevels[mCurrentLevel]->getTile(mMouseState.x / mTileWidth, mMouseState.y / mTileHeight, "Collision")->setID(219);
	}
	else if(keyDown(ALLEGRO_KEY_UP, mKeyboardState, mPrevKeyboardState))
	{
		changeLoadedLevel(true);
	}
	else if (keyDown(ALLEGRO_KEY_DOWN, mKeyboardState, mPrevKeyboardState))
	{
		changeLoadedLevel(false);
	}
	else if (keyDown(ALLEGRO_KEY_H, mKeyboardState, mPrevKeyboardState))
	{
		std::cout << "Toggle draw help" << std::endl;
		mDrawHelp = !mDrawHelp;
	}

	//copy to back buffer
	mpGridVisualizer->draw(*(mpGraphicsSystem->getBackBuffer()));

	mLevels[mCurrentLevel]->draw(mpGraphicsSystem);

	if (mDrawHelp)
	{
		std::cout << "Drawing Help" << std::endl;
		mpHelpMenu->draw(*(gpGame->getGraphicsSystem()->getBackBuffer()), 0, 0);
	}

	//should be last thing in processLoop
	Game::processLoop();
}

bool Editor::endLoop()
{
	return Game::endLoop();
}

void Editor::saveGrid( ofstream& theStream )
{
	mpGrid->save( theStream );
}

void Editor::loadGrid( std::ifstream& theStream )
{
}

void Editor::changeLoadedLevel(bool direction)
{
	//true is up, false is down
	if (direction)
	{
		mCurrentLevel++;

		if (mCurrentLevel >= mLevels.size())
		{
			mCurrentLevel = 0;
		}
	}
	else
	{
		mCurrentLevel--;
		if (mCurrentLevel < 0)
		{
			mCurrentLevel = mLevels.size() - 1;
		}
	}
}

bool Editor::keyDown(int key, ALLEGRO_KEYBOARD_STATE& currKeyState, ALLEGRO_KEYBOARD_STATE& prevKeyState)
{
	return (al_key_down(&currKeyState, key) && !al_key_down(&prevKeyState, key));
}