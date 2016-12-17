#ifndef _ENEMY_H
#define _ENEMY_H

#include "Unit.h"
#include <vector>

class GridPathfinder;

class Enemy : public Unit
{
public:
	Enemy(float speed, float frameTime, Vector2D pos);
	~Enemy();

	void update(double deltaTime);
	void draw(GraphicsBuffer& dest);

	void setPos(Vector2D pos) { mPos = pos; mSpawnPos = pos; }
	void setDrawDebug(bool drawDebug) { mDrawDebugLine = drawDebug; }
	void newPathfinder();
	void flee(double time);
	void findAPath();
	void respawn() { mPos = mSpawnPos; }
	void setCurrentLevel(int i) { mCurrLevel = i; }
	int getCurrentLevel() const { return mCurrLevel; }

private:
	void seek(int index, double time);
	void findAPath(Vector2D pos);
	float distanceBetween(Vector2D one, Vector2D two);
	void loadSpawnPos();

	GridPathfinder* mpPathfinder;
	Vector2D mSeekPos;
	Vector2D mSpawnPos = Vector2D(32, 128);
	std::vector<int> mNodesInPath;
	int mNodeSeekIndex = 0;
	int mCurrLevel = 0;
	bool mDrawDebugLine = true, mToDoor = false;
	bool mIsWandering;
};

#endif