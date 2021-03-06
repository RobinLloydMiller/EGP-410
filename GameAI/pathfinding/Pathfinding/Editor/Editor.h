#pragma once

#include "Game.h"
#include <fstream>

/*Editor - class to hold all application related info.

Dean Lawson
Champlain College
2011
*/

//forward declarations
class GraphicsBuffer;
class Sprite;
class Grid;
class GridVisualizer;
class GraphicsBuffer;

class Level;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class Editor: public Game
{
public:
	Editor();
	virtual ~Editor();

	inline Grid* getGrid() { return mpGrid; };
	inline GridVisualizer* getGridVisualizer() { return mpGridVisualizer; };

	virtual bool init();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	void saveGrid( std::ofstream& theStream );
	void loadGrid(std::ifstream& theStream);

private:
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;

	ALLEGRO_KEYBOARD_STATE mPrevKeyboardState;
	ALLEGRO_KEYBOARD_STATE mKeyboardState;
	ALLEGRO_MOUSE_STATE mMouseState;

	GraphicsBuffer* mpHelpMenuBuffer;
	Sprite* mpHelpMenu;

	bool mDrawHelp;

	bool keyDown(int key, ALLEGRO_KEYBOARD_STATE& currKeyState, ALLEGRO_KEYBOARD_STATE& prevKeyState);

	void changeLoadedLevel(bool direction);
};