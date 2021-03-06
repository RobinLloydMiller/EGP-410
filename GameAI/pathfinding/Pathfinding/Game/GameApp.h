#ifndef _GAMEAPP_H
#define _GAMEAPP_H

/*Game - class to hold all game related info.

Dean Lawson
Champlain College
2011
*/

#include "Game.h"
#include "Vector2D.h"
#include "Player.h"
#include "Enemy.h"
#include "GridVisualizer.h"
#include "GridGraph.h"
#include <vector>

//forward declarations
class GraphicsBuffer;
class Sprite;
class KinematicUnit;
class GameMessageManager;
class Grid;
class GridPathfinder;
class DebugDisplay;
class InputManager;
class SoundManager;

const float LOOP_TARGET_TIME = 16.6f;//how long should each frame of execution take? 30fps = 33.3ms/frame
const int NUM_MAPS = 4;

enum class PathfinderType
{
	DIJKSTRA,
	ASTAR
};

class GameApp: public Game
{
public:
	GameApp();
	~GameApp();

	virtual bool init();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	//accessors
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline SoundManager* getSoundManager() { return mpSoundManager; }
	inline GridVisualizer* getGridVisualizer() { return mpGridVisualizer; };
	inline GridPathfinder* getPathfinder() { return mpPathfinder; };
	inline Grid* getGrid() { return mGrids[mCurrentLevel]; };
	inline Grid* getGridAtIndex(int i) { return mGrids[i]; }
	inline GridGraph* getGridGraph() { return mGridGraphs[mCurrentLevel]; };
	inline GridGraph* getGridGraphAtIndex(int i) { return mGridGraphs[i]; }
	inline PathfinderType getPathfindingType() { return mPathfindingType; }
	inline Vector2D getPlayerPos() const { return mpPlayer->getPos(); }
	inline Player* getPlayer() const { return mpPlayer; }
	inline bool isPlayerInvincible() const { return mpPlayer->isInvincible(); }
	inline float getLoopTime() const { return LOOP_TARGET_TIME; }
	inline int getPlayerStateId() const { return mpPlayer->getPlayerStateId(); }

	void findAPath()
	{
		for (auto &it : mEnemies)
		{
			it->findAPath();
		}
	}

	void flee()
	{
		for (auto &it : mEnemies)
		{
			it->flee(LOOP_TARGET_TIME);
		}
	}

	void changeGrid(int index)
	{
		mCurrentLevel = index;
		mpGridVisualizer->setGridPointer(mGrids[index]);
		mpGridVisualizer->setDirty();
		for (auto &it : mEnemies)
		{
			it->newPathfinder();
		}
	}
  	void setDrawDebugLine(bool drawDebug) 
	{ 
		for (auto &it : mEnemies)
		{
			it->setDrawDebug(drawDebug);
		}
	}
	void respawnPlayer() 
	{ 
		mpPlayer->respawn();

		for (auto &it : mEnemies)
		{
			delete it;
		}

		mEnemies.clear();

		for (size_t i = 0; i < mEnemySpawnLocations.size(); ++i)
		{
			mEnemies.push_back(new Enemy(100, .2f, mEnemySpawnLocations[i]));
		}
	}
	void setPlayerDir(Direction newDir)
	{
		mpPlayer->setDir(newDir);
	}

	void loadLevel(int index);
	void spawnCandy();
	void loadEnemyPositions();
	void setTileIndexAtPixelXY(float x, float y);
	void switchPathfinding(PathfinderType newPathfinding);
	void setPlayerInvincible(bool invincible) { mpPlayer->setInvincible(invincible); }
	void toggleHelp() { mDrawHelp = !mDrawHelp; };

private:
	GameMessageManager* mpMessageManager;
	Grid* mGrids[NUM_MAPS];
	GridVisualizer* mpGridVisualizer;
	GridGraph* mGridGraphs[NUM_MAPS];
	DebugDisplay* mpDebugDisplay;
	InputManager* mpInputManager;
	SoundManager* mpSoundManager;

	GridPathfinder* mpPathfinder;
	PathfinderType mPathfindingType;

	bool mDrawHelp;
	GraphicsBuffer* mpHelpMenuBuffer;
	Sprite* mpHelpMenu;

	Player* mpPlayer;
	std::vector<Enemy*> mEnemies;
	std::vector<Vector2D> mEnemySpawnLocations;
};

#endif