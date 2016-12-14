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
const int NUM_MAPS = 2;

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
	inline Grid* getGrid() { return mGrids[mMapIndex]; };
	inline GridGraph* getGridGraph() { return mGridGraphs[mMapIndex]; };
	inline PathfinderType getPathfindingType() { return mPathfindingType; }
	inline Vector2D getPlayerPos() const { return mpPlayer->getPos(); }
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
		mMapIndex = index;
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
		delete mpPlayer; mpPlayer = new Player(150, .2f);

		for (auto &it : mEnemies)
		{
			delete it;
		}

		mEnemies.clear();

		mEnemies.push_back(new Enemy(100, .2f, Vector2D(500, 500)));
		mEnemies.push_back(new Enemy(100, .2f, Vector2D(200, 200)));
		mEnemies.push_back(new Enemy(100, .2f, Vector2D(800, 600)));
	}
	void setPlayerDir(Direction newDir)
	{
		mpPlayer->setDir(newDir);
	}

	void switchPathfinding(PathfinderType newPathfinding);
	void setPlayerInvincible(bool invincible) { mpPlayer->setInvincible(invincible); }

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

	Player* mpPlayer;
	std::vector<Enemy*> mEnemies;

	int mMapIndex = 0;
};

#endif