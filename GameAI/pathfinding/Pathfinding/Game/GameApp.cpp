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
#include <vector>

const IDType BACKGROUND_ID = ENDING_SEQUENTIAL_ID + 1;
const int GRID_SQUARE_SIZE = 32;
const std::string gFileName = "../Editor/pathgrid.txt";
const int NUM_COINS = 10;

GameApp::GameApp()
:mpMessageManager(NULL)
,mpInputManager(NULL)
,mpGridGraph(NULL)
,mpPathfinder(NULL)
,mpDebugDisplay(NULL)
,mpPlayer(NULL)
,mpEnemy(NULL)
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
	if( retVal == false )
	{

		return false;
	}

	mpMessageManager = new GameMessageManager();
	mpInputManager = new InputManager();

	//create and load the Grid, GridBuffer, and GridRenderer
	mGrids[0] = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	std::ifstream theStream( gFileName );
	mGrids[0]->load( theStream );

	mGrids[1] = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	std::ifstream theStream2("../Editor/pathgrid2.txt");
	mGrids[1]->load(theStream2);

	mpGridVisualizer = new GridVisualizer(mGrids[mMapIndex]);

	//create the GridGraph for pathfinding
	mpGridGraph = new GridGraph(mGrids[mMapIndex]);
	//init the nodes and connections
	mpGridGraph->init();

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

	mpPathfinder = new AStarPathfinder(mpGridGraph);
	//mpPathfinder = new DepthFirstPathfinder(mpGridGraph);

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
	mpEnemy = new Enemy(100, .2f);

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

	delete mpGridGraph;
	mpGridGraph = NULL;

	delete mpPathfinder;
	mpPathfinder = NULL;

	delete mpDebugDisplay;
	mpDebugDisplay = NULL;

	delete mpInputManager;
	mpInputManager = NULL;

	delete mpPlayer;
	mpPlayer = NULL;

	delete mpEnemy;
	mpEnemy = NULL;
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
	mpEnemy->update(mLoopTargetTime / 1000.0);

	//std::cout << mpLoopTimer->getElapsedTime() << std::endl;

	mpEnemy->draw(*(mpGraphicsSystem->getBackBuffer()));
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
			mpPathfinder = new DijkstraPathfinder(mpGridGraph);
			break;
		case PathfinderType::ASTAR:
			mpPathfinder = new AStarPathfinder(mpGridGraph);
			break;
	}

	mPathfindingType = newPathfinding;

	PathfindingDebugContent* pContent = new PathfindingDebugContent(mpPathfinder);
	mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), pContent);
}
