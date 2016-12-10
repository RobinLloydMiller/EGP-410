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

private:
	void seek(int index, double time);
	void findAPath();

	GridPathfinder* mpPathfinder;
	bool mSeeking = false;
	Vector2D mSeekPos;
	std::vector<int> mNodesInPath;
	int mNodeSeekIndex = 0;
};

#endif