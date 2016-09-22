/*main.cpp
 *	Adapted from: Example program for the Allegro library, by Shawn Hargreaves.
 *	Sets up all systems and runs the main game loop until it is time to quit.
 *
 *	Dean Lawson
 *	Champlain College
 *	2011
 *
 */
#define ALLEGRO_USE_CONSOLE

#include <stdio.h>

#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

 //crtdbg.h is a file exclusive to visual studio this prevents it from being compiled unless with visual studio
#ifdef _MSC_VER
#include <crtdbg.h>
#else
#define _ASSERT(expr) ((void)0)

#define _ASSERTE(expr) ((void)0)
#endif

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "KinematicUnit.h"
#include "DeanLib/Timer.h"
#include "DeanLib/PerformanceTracker.h"
#include "DeanLib/MemoryTracker.h"

using namespace std;

PerformanceTracker* gpPerformanceTracker = NULL;

int main(int argc, char **argv)
{
	gpPerformanceTracker = new PerformanceTracker();

	gpPerformanceTracker->startTracking("init");

	//create the global game object
	gpGame = new Game;
	//init the game
	bool goodGame = gpGame->init();
	if(!goodGame) 
	{
		fprintf(stderr, "failed to initialize Game object!\n");
		return -1;
	}

	gpPerformanceTracker->stopTracking("init");
	cout << "initialization took:" << gpPerformanceTracker->getElapsedTime("init") << "ms\n";

	bool shouldExit = false;

	//game loop
	while( !shouldExit )
	{
		gpPerformanceTracker->clearTracker("loop");
		gpPerformanceTracker->startTracking("loop");

		gpGame->beginLoop();

		gpPerformanceTracker->clearTracker("draw");
		gpPerformanceTracker->startTracking("draw");

		gpGame->processLoop();

		gpPerformanceTracker->stopTracking("draw");

		shouldExit = gpGame->endLoop();

		gpPerformanceTracker->stopTracking("loop");
		cout << "loop took:" << gpPerformanceTracker->getElapsedTime("loop") << "ms";
		cout << "draw took:" << gpPerformanceTracker->getElapsedTime("draw") << "ms\n";

	}

	gpGame->cleanup();
	delete gpGame;
	gpGame = NULL;

	delete gpPerformanceTracker;
	gMemoryTracker.reportAllocations( cout );
	system("pause");

	return 0;
}