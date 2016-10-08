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
In the folder ./GameAI/steering there is a.sln file which can be opened in Visual Studio as well as all source code and assets.  
The .sln will open the Visual Studio solution. 
All Allegro files are already linked in the Visual Studio solution so you can build the program as Win32 and Debug  
by using the build button in Visual Studio. Will build in Visual Studio 2015. Requires a re-compile of the DeanLib library
to run in older versions of Visual Studio.
 * If you want to build for Win64 or release mode in Visual Studio you can find the appropriate binaries for Allegro  
   And replace the current ones to do so. You will also need to rebuild DeanLib for the target platform  
   DeanLib is currently built for Win32 Debug.  

#Program Controls
F - Add a unit with Wander and Flee behavior relative to the player according to assignment specifications.  
S - Add a unit with Wander and Seek behavior relative to the player according to assignment specifications.  
D - Deletes a random unit that is not the player. When no non-player units are left the game closes.  
Left Click - Player moves towards the mouse location. The mouse cursor is replaced by x:y coordinates on screen.  
I - Toggles display of debug properties in left corner of the screen. The black text is the property currently selected.
+ - Increases value for all units on screen.
- - Decrease value for all units on screen. Value cannot drop below 0.
V - Select Max Velocity control.
R - Select Reaction Radius control.
A - Select Max Rotational Velocity control.
M - Select Max Acceleration control.
ESC - Closes the game.  

#[GitHub Link] (https://github.com/theMagicDunky/EGP-410)