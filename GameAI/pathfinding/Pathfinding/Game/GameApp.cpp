#include <allegro5/allegro.h>
#include "GameApp.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Grid.h"
#include "GridGraph.h"
#include "Connection.h"
#include "Path.h"
#include "DepthFirstPathfinder.h"
#include "Pathfinder.h"
#include "GridPathfinder.h"
#include "GridVisualizer.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"
#include "InputManager.h"
#include "DijkstraPathfinder.h"
#include "AStarPathfinder.h"

#include <fstream>

const IDType BACKGROUND_ID = ENDING_SEQUENTIAL_ID + 1;
const int GRID_SQUARE_SIZE = 32;
const std::string gFileName = "../Editor/pathgrid.txt";
const int NUM_COINS = 10;

GameApp::GameApp()
:mpMessageManager(NULL)
,mpInputManager(NULL)
,mpPathfinder(NULL)
,mpDebugDisplay(NULL)
,mpPlayer(NULL)
{
	mLoopTargetTime = LOOP_TARGET_TIME;
}

GameApp::~GameApp()
{
	cleanup();
}

bool GameApp::init()
{
	bool retVal = Game::init();
	if (retVal == false)
	{

		return false;
	}

	mpMessageManager = new GameMessageManager();
	mpInputManager = new InputManager();

	//create and load the Grid, GridBuffer, and GridRenderer
	mGrids[0] = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	std::ifstream theStream(gFileName);
	mGrids[0]->load(theStream);

	mGrids[1] = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	std::ifstream theStream2("../Editor/pathgrid2.txt");
	mGrids[1]->load(theStream2);

	mGridGraphs[0] = new GridGraph(mGrids[0]);
	mGridGraphs[0]->init();

	mGridGraphs[1] = new GridGraph(mGrids[1]);
	mGridGraphs[1]->init();

	mpGridVisualizer = new GridVisualizer(mGrids[mMapIndex]);

	/*adding coins here randomly to the map*/

	for (int i = 0; i < NUM_COINS; ++i)
	{
		int x, y;
		do
		{
			x = rand() % mGrids[mMapIndex]->getPixelWidth();
			y = rand() % mGrids[mMapIndex]->getPixelHeight();
		} while (mGrids[mMapIndex]->getValueAtPixelXY(x, y) != 0);
		mGrids[mMapIndex]->setValueAtPixelXY(x, y, 2);
	}

	{
		int x, y;
		do
		{
			x = rand() % mGrids[mMapIndex]->getPixelWidth();
			y = rand() % mGrids[mMapIndex]->getPixelHeight();
		} while (mGrids[mMapIndex]->getValueAtPixelXY(x, y) != 0 && mGrids[mMapIndex]->getValueAtPixelXY(x, y) != 2);
		mGrids[mMapIndex]->setValueAtPixelXY(x, y, 3);
	}

	//exit doors for now
	//used in flee pathfinding
	mGrids[mMapIndex]->setValueAtPixelXY(32, 32, 4);
	mGrids[mMapIndex]->setValueAtPixelXY(32, 750, 4);
	mGrids[mMapIndex]->setValueAtPixelXY(1000, 32, 4);
	mGrids[mMapIndex]->setValueAtPixelXY(1000, 750, 4);

	mpPathfinder = new AStarPathfinder(mGridGraphs[mMapIndex]);

	mPathfindingType = PathfinderType::ASTAR;

	//load buffers
	mpGraphicsBufferManager->loadBuffer( BACKGROUND_ID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( BACKGROUND_ID );

	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
	}

	mpGraphicsBufferManager->loadBuffer(69, "bee.png");
	mpGraphicsBufferManager->loadBuffer(70, "bee_fly.png");
	mpPlayer = new Player(150, .2f);

	mpGraphicsBufferManager->loadBuffer(71, "enemy.png");

	mEnemies.push_back(new Enemy(100, .2f));
	mEnemies.push_back(new Enemy(100, .2f, Vector2D(64, 96)));
	mEnemies.push_back(new Enemy(100, .2f, Vector2D(96, 128)));

	//debug display
	PathfindingDebugContent* pContent = new PathfindingDebugContent( mpPathfinder );
	mpDebugDisplay = new DebugDisplay( Vector2D(0,12), pContent );

	mpMasterTimer->start();
	return true;
}

void GameApp::cleanup()
{
	delete mpMessageManager;
	mpMessageManager = NULL;

	for (int i = 0; i < 2; ++i)
	{
		delete mGrids[i];
		mGrids[i] = NULL;
	}

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	for (int i = 0; i < 2; ++i)
	{
		delete mGridGraphs[i];
		mGridGraphs[i] = NULL;
	}

	delete mpPathfinder;
	mpPathfinder = NULL;

	delete mpDebugDisplay;
	mpDebugDisplay = NULL;

	delete mpInputManager;
	mpInputManager = NULL;

	delete mpPlayer;
	mpPlayer = NULL;

	delete mEnemies[0];
	mEnemies[0] = NULL;
	delete mEnemies[1];
	mEnemies[1] = NULL;
	delete mEnemies[2];
	mEnemies[2] = NULL;
}

void GameApp::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void GameApp::processLoop()
{
	//get back buffer
	GraphicsBuffer* pBackBuffer = mpGraphicsSystem->getBackBuffer();
	//copy to back buffer
	mpGridVisualizer->draw( *pBackBuffer );
#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
	//mpPathfinder->drawVisualization(mpGrid2, pBackBuffer);
#endif

	mpGridVisualizer->flipBuffer(*pBackBuffer);

	mpDebugDisplay->draw( pBackBuffer );

	mpMessageManager->processMessagesForThisframe();

	mpInputManager->update();

	//mpPlayer->update(mpLoopTimer->getElapsedTime());
	mpPlayer->update(mLoopTargetTime / 1000.0);

	for (auto &it : mEnemies)
	{
		it->update(mLoopTargetTime / 1000.0);
	}

	//std::cout << mpLoopTimer->getElapsedTime() << std::endl;

	for (auto &it : mEnemies)
	{
		it->draw(*(mpGraphicsSystem->getBackBuffer()));
	}

	mpPlayer->draw(*(mpGraphicsSystem->getBackBuffer()));

	//should be last thing in processLoop
	Game::processLoop();
}

bool GameApp::endLoop()
{
	return Game::endLoop();
}

void GameApp::switchPathfinding(PathfinderType newPathfinding)
{
	delete mpPathfinder;
	mpPathfinder = NULL;

	delete mpDebugDisplay;
	mpDebugDisplay = NULL;

	switch (newPathfinding)
	{
		case PathfinderType::DIJKSTRA:
			mpPathfinder = new DijkstraPathfinder(mGridGraphs[0]);
			break;
		case PathfinderType::ASTAR:
			mpPathfinder = new AStarPathfinder(mGridGraphs[0]);
			break;
	}

	mPathfindingType = newPathfinding;

	PathfindingDebugContent* pContent = new PathfindingDebugContent(mpPathfinder);
	mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), pContent);
}
