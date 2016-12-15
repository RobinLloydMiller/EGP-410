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

const int GRID_SQUARE_SIZE = 64;
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

	mpMainLevel = new Level("../assets/pathgrid.tmx");
	mpMainLevel->getTileSize(mTileHeight, mTileWidth);
	
	mpMasterTimer->start();
	return true;
}

void Editor::cleanup()
{
	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGrid;
	mpGrid = NULL;

	delete mpMainLevel;
	mpMainLevel = NULL;
}

void Editor::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void Editor::processLoop()
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state( &mouseState );
	ALLEGRO_KEYBOARD_STATE keyboardState;
	al_get_keyboard_state(&keyboardState);

	if( al_mouse_button_down( &mouseState, 1 ) )//left mouse click
	{
		mpMainLevel->getTile(mouseState.x / mTileWidth, mouseState.y / mTileHeight, "Collision")->setID(1);

		//mpGrid->setValueAtPixelXY( mouseState.x, mouseState.y, BLOCKING_VALUE );
		//mpGridVisualizer->setModified();
	}
	else if( al_mouse_button_down( &mouseState, 2 ) )//right mouse down
	{
		mpMainLevel->getTile(mouseState.x / mTileWidth, mouseState.y / mTileHeight, "Collision")->setID(0);

		//mpGrid->setValueAtPixelXY( mouseState.x, mouseState.y, CLEAR_VALUE );
		//mpGridVisualizer->setModified();
	}

	else if (al_key_down(&keyboardState, ALLEGRO_KEY_1))
	{
		mpMainLevel->getTile(mouseState.x / mTileWidth, mouseState.y / mTileHeight, "Collision")->setID(138);
	}
	else if (al_key_down(&keyboardState, ALLEGRO_KEY_2))
	{
		mpMainLevel->getTile(mouseState.x / mTileWidth, mouseState.y / mTileHeight, "Collision")->setID(155);
	}
	else if (al_key_down(&keyboardState, ALLEGRO_KEY_3))
	{
		mpMainLevel->getTile(mouseState.x / mTileWidth, mouseState.y / mTileHeight, "Collision")->setID(131);
	}
	else if (al_key_down(&keyboardState, ALLEGRO_KEY_4))
	{
		mpMainLevel->getTile(mouseState.x / mTileWidth, mouseState.y / mTileHeight, "Collision")->setID(145);
	}
	else if (al_key_down(&keyboardState, ALLEGRO_KEY_5))
	{
		mpMainLevel->getTile(mouseState.x / mTileWidth, mouseState.y / mTileHeight, "Collision")->setID(140);
	}
	else if (al_key_down(&keyboardState, ALLEGRO_KEY_6))
	{
		mpMainLevel->getTile(mouseState.x / mTileWidth, mouseState.y / mTileHeight, "Collision")->setID(268);
	}
	else if (al_key_down(&keyboardState, ALLEGRO_KEY_7))
	{
		mpMainLevel->getTile(mouseState.x / mTileWidth, mouseState.y / mTileHeight, "Collision")->setID(219);
	}

	//copy to back buffer
	mpGridVisualizer->draw(*(mpGraphicsSystem->getBackBuffer()));

	mpMainLevel->draw(mpGraphicsSystem);
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
	mpGrid->load(theStream);
}
