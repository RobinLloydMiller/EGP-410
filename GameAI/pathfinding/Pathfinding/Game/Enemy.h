#ifndef _ENEMY_H
#define _ENEMY_H

#include "Unit.h"
#include "Path.h"

class GridPathfinder;

class Enemy : public Unit
{
public:
	Enemy(float speed, float frameTime);
	~Enemy();

	void update(double deltaTime);
	void draw(GraphicsBuffer& dest);

	void setDrawDebug(bool drawDebug) { mDrawDebugLine = drawDebug; }

private:
	void seek(int index, double time);
	void findAPath();

	GridPathfinder* mpPathfinder;
	Vector2D mSeekPos;
	Vector2D mSpawnPos = Vector2D(32, 128);
	std::vector<int> mNodesInPath;
	int mNodeSeekIndex = 0;
	bool mDrawDebugLine = false;
};

#endif