#include "Player.h"
#include "GameApp.h"
#include "Grid.h"
#include "GridVisualizer.h"
#include "GraphicsBufferManager.h"
#include "GraphicsBuffer.h"
#include "Animation.h"
#include "Sprite.h"
#include "NoCandyState.h"
#include "CandyState.h"
#include "Level.h"

Player::Player(float speed, float frameTime)
:Unit(speed, frameTime)
{
	GraphicsBufferManager* pBuffMan = gpGameApp->getGraphicsBufferManager();

	mpAnime->addSprite(new Sprite(pBuffMan->getBuffer(69), 0, 0, pBuffMan->getBuffer(69)->getWidth(), pBuffMan->getBuffer(69)->getHeight()));
	mpAnime->addSprite(new Sprite(pBuffMan->getBuffer(70), 0, 0, pBuffMan->getBuffer(70)->getWidth(), pBuffMan->getBuffer(70)->getHeight()));

	mPos = mSpawnPos;

	initStateMachine();
}

Player::~Player()
{
	delete mpStateMachine;
	delete mpNoCandyState;
	delete mpCandyState;
	delete mpToCandyState;
	delete mpToNoCandyState;
}

void Player::update(double deltaTime)
{
	Unit::update(deltaTime);

	Vector2D collPoint;

	//check collision with coin
	/*collPoint = gpGameApp->getGrid()->isCollidingAtPixelXY(mPos.getX(), mPos.getY(), 2);
	if (collPoint != Vector2D(-1, -1))
	{
		mScore++;
		gpGameApp->getGrid()->setValueAtPixelXY(collPoint.getX(), collPoint.getY(), 0);
		gpGameApp->getGridVisualizer()->setDirty();
	}*/

	collPoint = gpGameApp->getGrid()->isCollidingAtPixelXY(mPos.getX(), mPos.getY(), 140);
	if (collPoint != Vector2D(-1, -1))
	{
		gpGameApp->setTileIndexAtPixelXY(collPoint.getX(), collPoint.getY());
		dynamic_cast<NoCandyState*>(mpNoCandyState)->gotCandy();
	}


	collPoint = gpGameApp->getGrid()->isCollidingAtPixelXY(mPos.getX(), mPos.getY(), 138);
	if (collPoint != Vector2D(-1, -1))
	{
		gpGameApp->loadLevel(0);
	}
	collPoint = gpGameApp->getGrid()->isCollidingAtPixelXY(mPos.getX(), mPos.getY(), 155);
	if (collPoint != Vector2D(-1, -1))
	{
		gpGameApp->loadLevel(1);
	}
	collPoint = gpGameApp->getGrid()->isCollidingAtPixelXY(mPos.getX(), mPos.getY(), 131);
	if (collPoint != Vector2D(-1, -1))
	{
		gpGameApp->loadLevel(2);
	}
	collPoint = gpGameApp->getGrid()->isCollidingAtPixelXY(mPos.getX(), mPos.getY(), 145);
	if (collPoint != Vector2D(-1, -1))
	{
		gpGameApp->loadLevel(3);
	}

	mpStateMachine->update();
}

void Player::draw(GraphicsBuffer& dest)
{
	Unit::draw(dest);
}

void Player::initStateMachine()
{
	mpStateMachine = new StateMachine();

	mpNoCandyState = new NoCandyState(0);
	mpCandyState = new CandyState(1);

	mpToNoCandyState = new StateTransition(NO_CANDY_TRANSISTION, 0);
	mpToCandyState = new StateTransition(CANDY_TRANSISTION, 1);

	mpNoCandyState->addTransition(mpToCandyState);
	mpCandyState->addTransition(mpToNoCandyState);

	mpStateMachine->addState(mpNoCandyState);
	mpStateMachine->addState(mpCandyState);

	mpStateMachine->setInitialStateID(0);
}