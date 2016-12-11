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

//forward declarations
class GraphicsBuffer;
class Sprite;
class KinematicUnit;
class GameMessageManager;
class Grid;
class GridVisualizer;
class GridGraph;
class GridPathfinder;
class DebugDisplay;
class InputManager;

const float LOOP_TARGET_TIME = 16.6f;//how long should each frame of execution take? 30fps = 33.3ms/frame

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
	inline GridVisualizer* getGridVisualizer() { return mpGridVisualizer; };
	inline GridPathfinder* getPathfinder() { return mpPathfinder; };
	inline Grid* getGrid() { return mpGrid; };
	inline GridGraph* getGridGraph() { return mpGridGraph; };
	inline PathfinderType getPathfindingType() { return mPathfindingType; }
	inline Vector2D getPlayerPos() const { return mpPlayer->getPos(); }

	void setDrawDebugLine(bool drawDebug) { mpEnemy->setDrawDebug(drawDebug); }
	void respawnPlayer() { delete mpPlayer; mpPlayer = new Player(150, .2f); delete mpEnemy; mpEnemy = new Enemy(100, .2f); }
	void setPlayerDir(Direction newDir)
	{
		mpPlayer->setDir(newDir);
	}

	void switchPathfinding(PathfinderType newPathfinding);

private:
	GameMessageManager* mpMessageManager;
	Grid* mpGrid, *mpGrid2, *theRealGrid;
	GridVisualizer* mpGridVisualizer;
	GridGraph* mpGridGraph;
	DebugDisplay* mpDebugDisplay;
	InputManager* mpInputManager;

	GridPathfinder* mpPathfinder;
	PathfinderType mPathfindingType;

	Player* mpPlayer;
	Enemy* mpEnemy;
};

#endif