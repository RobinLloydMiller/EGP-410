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
#include "SoundManager.h"
#include "Level.h"

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
,mpSoundManager(NULL)
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
	mpSoundManager = new SoundManager();

	mpSoundManager->addSound("coinSound.ogg", CoinSound);
	mpSoundManager->playSound(CoinSound);

	mLevels.push_back(new Level("../assets/Level1.tmx", "../assets/pathgrid.txt"));
	mLevels.push_back(new Level("../assets/Level2.tmx", "../assets/pathgrid2.txt"));
	mLevels.push_back(new Level("../assets/Level3.tmx", "../assets/pathgrid3.txt"));
	mLevels.push_back(new Level("../assets/Level4.tmx", "../assets/pathgrid4.txt"));

	//create and load the Grid, GridBuffer, and GridRenderer
	mGrids[0] = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	std::ifstream theStream("../assets/pathgrid.txt");
	mGrids[0]->load(theStream);

	mGrids[1] = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	std::ifstream theStream2("../assets/pathgrid2.txt");
	mGrids[1]->load(theStream2);

	mGrids[2] = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	std::ifstream theStream3("../assets/pathgrid3.txt");
	mGrids[2]->load(theStream3);

	mGrids[3] = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	std::ifstream theStream4("../assets/pathgrid4.txt");
	mGrids[3]->load(theStream4);

	for (int i = 0; i < NUM_MAPS; ++i)
	{
		mGridGraphs[i] = new GridGraph(mGrids[i]);
		mGridGraphs[i]->init();
	}

	mCurrentLevel = 0;

	mpGridVisualizer = new GridVisualizer(mGrids[mCurrentLevel]);

	/*adding coins here randomly to the map*/

	/*for (int i = 0; i < NUM_COINS; ++i)
	{
		int x, y;
		do
		{
			x = rand() % mGrids[mMapIndex]->getPixelWidth();
			y = rand() % mGrids[mMapIndex]->getPixelHeight();
		} while (mGrids[mMapIndex]->getValueAtPixelXY(x, y) != 0);
		mGrids[mMapIndex]->setValueAtPixelXY(x, y, 2);
	}*/

	mLevels[0]->getTileSize(mTileHeight, mTileWidth);

	//exit doors for now
	//used in flee pathfinding
	//mGrids[mMapIndex]->setValueAtPixelXY(32, 32, 4);
	//mGrids[mMapIndex]->setValueAtPixelXY(32, 750, 4);
	//mGrids[mMapIndex]->setValueAtPixelXY(1000, 32, 4);
	//mGrids[mMapIndex]->setValueAtPixelXY(1000, 750, 4);

	mpPathfinder = new AStarPathfinder(mGridGraphs[mCurrentLevel]);

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

	//debug display
	PathfindingDebugContent* pContent = new PathfindingDebugContent( mpPathfinder );
	mpDebugDisplay = new DebugDisplay( Vector2D(0,12), pContent );	


	loadEnemyPositions();

	mEnemySpawnLocations.push_back(Vector2D(1, 1));

	for (size_t i = 0; i < mEnemySpawnLocations.size(); ++i)
	{
		mEnemies.push_back(new Enemy(75, .2f, mEnemySpawnLocations[i]));
	}

	loadLevel(mCurrentLevel);
	mpMasterTimer->start();

	return true;
}

void GameApp::cleanup()
{
	delete mpMessageManager;
	mpMessageManager = NULL;

	for (int i = 0; i < 4; ++i)
	{
		delete mGrids[i];
		mGrids[i] = NULL;
	}

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	for (int i = 0; i < NUM_MAPS; ++i)
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

	delete mpSoundManager;
	mpSoundManager = NULL;


	for (size_t i = 0; i < mEnemies.size(); ++i)
	{
		delete mEnemies[i];
		mEnemies[i] = NULL;
	}

	for (size_t i = 0; i < mLevels.size(); ++i)
	{
		delete mLevels[i];
		mLevels[i] = NULL;
	}
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
	//mpGridVisualizer->draw( *pBackBuffer );

	mLevels[mCurrentLevel]->draw(mpGraphicsSystem);

#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
	//mpPathfinder->drawVisualization(mpGrid2, pBackBuffer);
#endif

	//mpGridVisualizer->flipBuffer(*pBackBuffer);

	//mpDebugDisplay->draw( pBackBuffer );

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
		if(mCurrentLevel == it->getCurrentLevel())
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

void GameApp::loadLevel(int index)
{
	mCurrentLevel = index;

	int i = 0;

	while (mGrids[mCurrentLevel]->getValueAtIndex(i) != 268)
		++i;

	mpPlayer->setPos(mGrids[mCurrentLevel]->getULCornerOfSquare(i));
	for (auto &it : mEnemies)
	{
		if (it->getCurrentLevel() == mCurrentLevel)
			it->findAPath();
	}
}

void GameApp::loadEnemyPositions()
{
	int i = 0;

	while (mGrids[mCurrentLevel]->getValueAtIndex(i) != 219)
		++i;

	for (auto &it : mEnemies)
	{
		it->setPos(mGrids[mCurrentLevel]->getULCornerOfSquare(i));
	}
}

void GameApp::setTileIndexAtPixelXY(float x, float y)
{
	gpGameApp->getGrid()->setValueAtPixelXY(x, y, 0);
	gpGameApp->getLevel()->getTile(x / mTileWidth, y / mTileHeight, "Collision")->setID(0);
	mpGridVisualizer->setDirty();
}

void GameApp::spawnCandy()
{
	int x, y;
	do
	{
		x = rand() % mGrids[mCurrentLevel]->getPixelWidth();
		y = rand() % mGrids[mCurrentLevel]->getPixelHeight();
	} while (mGrids[mCurrentLevel]->getValueAtPixelXY(x, y) != 0);
	mGrids[mCurrentLevel]->setValueAtPixelXY(x, y, 140);
	mLevels[mCurrentLevel]->getTile(x / mTileWidth, y / mTileHeight, "Collision")->setID(140);
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
