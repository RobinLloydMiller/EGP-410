#include "Enemy.h"
#include "Animation.h"
#include "GameApp.h"
#include "Sprite.h"
#include "GraphicsBufferManager.h"
#include "GraphicsBuffer.h"
#include "AStarPathfinder.h"
#include "GridGraph.h"
#include "PathToMessage.h"
#include "GameMessageManager.h"
#include "Grid.h"
#include <math.h>

Enemy::Enemy(float speed, float frameTime)
:Unit(speed, frameTime)
{
	GraphicsBufferManager* pBuffMan = gpGameApp->getGraphicsBufferManager();

	mpAnime->addSprite(new Sprite(pBuffMan->getBuffer(71), 0, 0, pBuffMan->getBuffer(71)->getWidth(), pBuffMan->getBuffer(71)->getHeight()));

	mPos = Vector2D(32, 64);

	mpPathfinder = new AStarPathfinder(gpGameApp->getGridGraph());	

	//mDir = Direction::DOWN;

	findAPath();

	//
	mSpeed = 75;
}

Enemy::~Enemy()
{
	delete mpPathfinder;
}

void Enemy::update(double deltaTime)
{
	//getem
	if (!mSeeking)
	{
		//findAPath();
	}

	int index = mNodesInPath[mNodeSeekIndex];

	//std::cout << mNodeSeekIndex << " " << mNodesInPath.size() << std::endl;

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
			std::cout << "made it";
			++mNodeSeekIndex;
		}
	}

	//std::cout << "here: " << gpGameApp->getGrid()->getSquareIndexFromPixelXY(mPos.getX(), mPos.getY()) << " needs to be here " << index << std::endl;
	//std::cout << "seek index " << index << " current index: " << gpGameApp->getGrid()->getSquareIndexFromPixelXY(mPos.getX(), mPos.getY()) << std::endl;

	seek(index, deltaTime);

	
	Unit::update(deltaTime);
}

void Enemy::draw(GraphicsBuffer& dest)
{
	//mpPathfinder->drawVisualization(gpGameApp->getGrid(), &dest);
	Unit::draw(dest);
}

void Enemy::seek(int index, double time)
{
	Vector2D dest = gpGameApp->getGrid()->getULCornerOfSquare(index);
	Vector2D pos = dest - mPos;

	//std::cout << pos.getX() << "\t" << pos.getY() << std::endl;

	pos.normalize();
	//pos.setX(std::round(pos.getX()));
	//pos.setY(std::round(pos.getY()));

	std::cout << pos.getX() << " " << pos.getY() << std::endl;
	
	//mPos += pos * time * mSpeed;

	moveAndCheckCollision(mPos + (pos * time * mSpeed));

	if ((pos.getX() <= dest.getX() - 10 || pos.getX() >= dest.getX() + 10)
		&& (pos.getY() <= dest.getY() - 10 || pos.getY() >= dest.getY() + 10))
	{
		pos = dest;
	}

		//findAPath();

	/*if (mPos.getY() > pos.getY())
		mPos.setY(mPos.getY() - (mSpeed * time));
	else
		mPos.setY(mPos.getY() + (mSpeed * time));

	if (mPos.getX() > pos.getX())
		mPos.setX(mPos.getX() - (mSpeed * time));
	else
		mPos.setX(mPos.getX() + (mSpeed * time));*/
}

void Enemy::findAPath()
{
	GridGraph* pGridGraph = gpGameApp->getGridGraph();
	Grid* pGrid = gpGameApp->getGrid();
	int fromIndex = pGrid->getSquareIndexFromPixelXY((int)mPos.getX(), (int)mPos.getY());
	int toIndex = pGrid->getSquareIndexFromPixelXY((int)gpGameApp->getPlayerPos().getX(), (int)gpGameApp->getPlayerPos().getY());

	int i;

	if (mNodesInPath.size() == 0)
		i = fromIndex;
	else
		i = mNodesInPath[mNodesInPath.size() - 1];

	Node* pFromNode = pGridGraph->getNode(i);
	Node* pToNode = pGridGraph->getNode(gpGameApp->getGrid()->getSquareIndexFromPixelXY(gpGameApp->getPlayerPos().getX() + 16, gpGameApp->getPlayerPos().getY() + 16));
	if (pFromNode != NULL && pToNode != NULL)
	{
		mpPathfinder->findPath(pToNode, pFromNode);
		mNodesInPath = mpPathfinder->getNodesInPath();
	}

	//GameMessage* pMessage = new PathToMessage(mPos, gpGameApp->getPlayerPos(), mpPathfinder);
	//gpGameApp->getMessageManager()->addMessage(pMessage, 0);

	mNodeSeekIndex = 0;
	mSeeking = true;
}