#include "Enemy.h"
#include "Animation.h"
#include "GameApp.h"
#include "Sprite.h"
#include "GraphicsBufferManager.h"
#include "GraphicsBuffer.h"
#include "GameMessageManager.h"
#include "RespawnMessage.h"
#include "Grid.h"
#include "AStarPathfinder.h"
#include "GridGraph.h"
#include <math.h>

Enemy::Enemy(float speed, float frameTime, Vector2D pos)
:Unit(speed, frameTime)
{
	GraphicsBufferManager* pBuffMan = gpGameApp->getGraphicsBufferManager();

	mpAnime->addSprite(new Sprite(pBuffMan->getBuffer(71), 0, 0, pBuffMan->getBuffer(71)->getWidth(), pBuffMan->getBuffer(71)->getHeight()));

	mPos = pos;

	mpPathfinder = new AStarPathfinder(gpGameApp->getGridGraph());	

	findAPath();

	mSpeed = 75;
	mPos = mSpawnPos;
}

Enemy::~Enemy()
{
	delete mpPathfinder;
}

void Enemy::update(double deltaTime)
{

	//std::cout << mPos.getY() << std::endl;

	Unit::update(deltaTime);

	//getem
	int index = mNodesInPath[mNodeSeekIndex];

	if (gpGameApp->getGrid()->getSquareIndexFromPixelXY(std::ceil(mPos.getX() + 2), std::ceil(mPos.getY() + 2)) == index
		&& gpGameApp->getGrid()->getSquareIndexFromPixelXY(std::ceil(mPos.getX() + 30), std::ceil(mPos.getY()) + 30) == index)
	{
		if (mNodeSeekIndex == (mNodesInPath.size()) - 1)
		{
			mNodeSeekIndex = 0;
			findAPath();
		}
		else
		{
			++mNodeSeekIndex;
		}
	}

	/*if (gpGameApp->getPlayerStateId() == 0)
		seek(index, deltaTime);
	else
	{
		flee(deltaTime);
		seek(index, deltaTime);
	}*/

	seek(index, deltaTime);
}

void Enemy::draw(GraphicsBuffer& dest)
{
	mpPathfinder->drawVisualization(gpGameApp->getGrid(), &dest, mDrawDebugLine);
	Unit::draw(dest);
}

void Enemy::newPathfinder()
{
	delete mpPathfinder;
	mpPathfinder = new AStarPathfinder(gpGameApp->getGridGraph());
	mNodesInPath.clear();
	findAPath();
}

void Enemy::seek(int index, double time)
{
	Vector2D dest = gpGameApp->getGrid()->getULCornerOfSquare(index);
	Vector2D pos = dest - mPos;

	pos.normalize();

	moveAndCheckCollision(mPos + (pos * time * mSpeed));

	int buffer = 10;

	if ((pos.getX() <= dest.getX() - buffer || pos.getX() >= dest.getX() + buffer)
		&& (pos.getY() <= dest.getY() - buffer || pos.getY() >= dest.getY() + buffer))
	{
		pos = dest;
	}

	Vector2D playerPos = gpGameApp->getPlayerPos();

	//colliding with the player
	if ((abs(mPos.getX() - playerPos.getX()) * 2 < (32 + 32)) &&
		(abs(mPos.getY() - playerPos.getY()) * 2 < (32 + 32)))
	{
		if (!gpGameApp->isPlayerInvincible())
		{
			GameMessage* pMessage = new RespawnMessage();
			gpGameApp->getMessageManager()->addMessage(pMessage, 0);
		}
	}
}

void Enemy::flee(double time)
{
	Vector2D playerPos = gpGameApp->getPlayerPos();
	Vector2D ULCorner = Vector2D(32, 32);
	Vector2D URCorner = Vector2D(32, 750);
	Vector2D BLCorner = Vector2D(1000, 32);
	Vector2D BRCorner = Vector2D(1000, 750);

	float distToUL = std::abs(ULCorner.getX() - playerPos.getX()) + std::abs(ULCorner.getY() - playerPos.getY());
	float distToBL = std::abs(BLCorner.getX() - playerPos.getX()) + std::abs(BLCorner.getY() - playerPos.getY());
	float distToUR = std::abs(URCorner.getX() - playerPos.getX()) + std::abs(URCorner.getY() - playerPos.getY());
	float distToBR = std::abs(BRCorner.getX() - playerPos.getX()) + std::abs(BRCorner.getY() - playerPos.getY());

	float largest = distToUL;
	Vector2D largestPos = ULCorner;

	if (distToBL > largest)
	{
		largest = distToBL;
		largestPos = BLCorner;
	}
	if (distToUR > largest)
	{
		largest = distToUR;
		largestPos = URCorner;
	}
	if (distToBR > largest)
	{
		largest = distToBR;
		largestPos = BRCorner;
	}

	mNodesInPath.clear();

	findAPath(largestPos);
	//Vector2D pos = mPos - gpGameApp->getPlayerPos();
	//pos.normalize();
	//moveAndCheckCollision(mPos + (pos * time * mSpeed));
}

void Enemy::findAPath(Vector2D pos)
{
	GridGraph* pGridGraph = gpGameApp->getGridGraph();
	Grid* pGrid = gpGameApp->getGrid();
	int fromIndex = pGrid->getSquareIndexFromPixelXY((int)mPos.getX(), (int)mPos.getY());
	int toIndex = pGrid->getSquareIndexFromPixelXY((int)pos.getX(), (int)pos.getY());

	int i;

	if (mNodesInPath.size() == 0)
		i = fromIndex;
	else
		i = mNodesInPath[mNodesInPath.size() - 1];

	Node* pFromNode = pGridGraph->getNode(i);
	Node* pToNode = pGridGraph->getNode(gpGameApp->getGrid()->getSquareIndexFromPixelXY(pos.getX() + 16, pos.getY() + 16));
	if (pFromNode != NULL && pToNode != NULL)
	{
		mpPathfinder->findPath(pToNode, pFromNode);
		mNodesInPath = mpPathfinder->getNodesInPath();
	}

	mNodeSeekIndex = 0;
}

void Enemy::findAPath()
{

	GridGraph* pGridGraph = gpGameApp->getGridGraph();
	Grid* pGrid = gpGameApp->getGrid();
	int fromIndex = pGrid->getSquareIndexFromPixelXY((int)mPos.getX(), (int)mPos.getY());
	int toIndex = pGrid->getSquareIndexFromPixelXY((int)gpGameApp->getPlayerPos().getX(), (int)gpGameApp->getPlayerPos().getY());

	Node* pFromNode = pGridGraph->getNode(fromIndex);
	Node* pToNode = pGridGraph->getNode(gpGameApp->getGrid()->getSquareIndexFromPixelXY(gpGameApp->getPlayerPos().getX() + 16, gpGameApp->getPlayerPos().getY() + 16));
	if (pFromNode != NULL && pToNode != NULL)
	{
		mpPathfinder->findPath(pToNode, pFromNode);
		mNodesInPath = mpPathfinder->getNodesInPath();
	}

	mNodeSeekIndex = 0;
}