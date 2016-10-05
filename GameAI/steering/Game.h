#pragma once

#include "Trackable.h"
#include "StateManager.h"
#include "InputManager.h"
#include "PerformanceTracker.h"
#include "Defines.h"
#include "KinematicUnitManager.h"
#include "StateManager.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <string>

class GraphicsSystem;
class GraphicsBuffer;
class GraphicsBufferManager;
class SpriteManager;
class KinematicUnit;
class KinematicUnitManager;
class GameMessageManager;
class Timer;

const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_ICON_SPRITE_ID = 1;
const IDType AI_ICON_SPRITE_ID = 2;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class Game:public Trackable
{
public:
	Game();
	~Game();

	bool init();//returns true if no errors, false otherwise
	void cleanup();

	//game loop
	void beginLoop();
	void processLoop();
	bool endLoop();

	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline KinematicUnitManager* getKinematicUnitManager() const { return mpKinematicUnitManager; };
	inline KinematicUnit* getPlayer() const { return mpKinematicUnitManager->getPlayer(); };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };
	inline ALLEGRO_FONT* getFont() const { return mpFont; };
	inline void exitGame() { mShouldExit = true; };
	inline Sprite* getEnemySprite() const { return mpEnemyArrow; };
	inline GameState getCurrState() const { return mpStateManager->getCurrState(); };
	inline EnemyProperty getCurrProperty() const { return mpStateManager->getCurrProperty(); };
	inline float getEnemyMaxVelocity() const { return mpKinematicUnitManager->getUnit(0)->getMaxVelocity(); };
	inline float getEnemyReactionRadius() const { return mpKinematicUnitManager->getUnit(0)->getSteering()->getRadius(); };
	inline float getEnemyAngularVelocity() const { return mpKinematicUnitManager->getUnit(0)->getSteering()->getAngular(); };
	inline float getEnemyMaxAcceleration() const { return mpKinematicUnitManager->getUnit(0)->getMaxAcceleration(); };
	
	//i know this could be easier with a bool but i hope this can be expanded to include other game states
	void toggleDebugState()
	{
		if (mpStateManager->getCurrState() == DEBUG_OFF)
			mpStateManager->setCurrState(DEBUG_ON);
		else
			mpStateManager->setCurrState(DEBUG_OFF);
	}
	inline void setCurrProperty(EnemyProperty prop) { mpStateManager->setCurrProperty(prop); }

private:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	KinematicUnitManager* mpKinematicUnitManager;
	SpriteManager* mpSpriteManager;
	GameMessageManager* mpMessageManager;
	InputManager* mpInputManager;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	bool mShouldExit;
	Sprite* mpEnemyArrow;
	StateManager* mpStateManager;

	//should be somewhere else
	ALLEGRO_FONT* mpFont;
	ALLEGRO_SAMPLE* mpSample;
	IDType mBackgroundBufferID;
	IDType mPlayerIconBufferID;
	IDType mEnemyIconBufferID;
};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge

extern Game* gpGame;
extern PerformanceTracker* gpPerformanceTracker;