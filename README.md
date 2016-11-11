# EGP-410
Template projects for base code for EGP 410 assignments.

#This repository contains three major directories:
 * DeanLib - Base utility library provided by Dean Lawson. Memory tracking and basic vector mathematics utilities.
 * External Libs - Allegro 5.0.10 support libraries.
 * Game AI - Base source code for EGP 410 Assignments
   * pathfinding
   * state machine
   * steering

#Building Instructions
In the folder ./GameAI/pathfinding there is a.sln file which can be opened in Visual Studio as well as all source code and assets.  
The .sln will open the Visual Studio solution. 
All Allegro files are already linked in the Visual Studio solution so you can build the program as Win32 and Debug  
by using the build button in Visual Studio. Will build in Visual Studio 2015. Requires a re-compile of the DeanLib library
to run in older versions of Visual Studio.
 * If you want to build for Win64 or release mode in Visual Studio you can find the appropriate binaries for Allegro  
   And replace the current ones to do so. You will also need to rebuild DeanLib for the target platform  
   DeanLib is currently built for Win32 Debug.  

#Program Controls

This Visual Studio solution contains two execuatable projects, Game and Editor.
The game project is used to demonstrate Dijkstra and A* pathfinding algorithms.
The editor project is used to draw a map of walls for the game to pathfind around.


Game:
Left Mouse Click - place start and goal locations
	* The first click will place the start location and draw it
	* Once the start is placed another click will place the goal and run pathfinding between the points

A - Switch pathfinding to A* algorithm (A* is the default pathfinding on startup)
D - Switch pathfinding to Dijkstra algorithm
ESC - Close the program.

Editor:
Left Mouse Click - Place a wall on the tile map
Right Mouse Click - Erase a wall on the tile map

S - Save the current map. The game project will use whatever map was last saved in the editor this way
ESC - Close the program.

#[GitHub Link] (https://github.com/theMagicDunky/EGP-410/commit/38806015d7e3f9d3b994a92badf225852aacd985)