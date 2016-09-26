# EGP-410
Template projects for base code for EGP 410 assignments.

#This repository contains three major directories:
 * DeanLib - Base utility library provided by Dean Lawson. Memory tracking and basic vector mathematics utilities.
 * External Libs - Allegro 5.0.10 support libraries.
 * Game AI - Base source code for EGP 410 Assignments
   * pathfinding
   * state machine
   * steering

Building instructions are left up to the student. 

#Building Instructions
In the folder ./GameAI/steering there are multiple Visual Studio project files and a .sln file.
Any of those can be used to open the solution in Visual Studio.
All Allegro files are already linked in the Visual Studio solution so you can build the program as Win32 and Debug
by using the build button in Visual Studio.
 * If you want to build for Win64 or release mode in Visual Studio you can find the appropriate binaries for Allegro
   And replace the current ones to do so. You will also need to rebuild DeanLib for the target platform
   DeanLib is currently built for Win32 Debug.

#Program Controls
A - Add a unit with Dynamic Arrive relative to the player according to assignment specifications.
S - Add a unit with Dynamic Seek relative to the player according to assignment specifications.
D - Deletes a random unit that is not the player. When the last non-player unit is deleted the game closes.
Left Click - Player moves towards the mouse location. The mouse cursor is replaced by x:y coordinates on screen.
ESC - Closes the game.
