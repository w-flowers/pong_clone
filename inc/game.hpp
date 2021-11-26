
/********************************************************************************
* Pong Clone - Game (game.hpp) 
*
* A class that manages the running of the game as a whole. Contains the run
* method and the event loop.
*
* Author: William Flowers
********************************************************************************/

#ifndef GAME_HPP

#define GAME_HPP

#include "gui.hpp"

#include "field.hpp"

const int GUI_SIZE_X {500};

const int GUI_SIZE_Y {500};

namespace Game
{
   //A containing method for all the game code, to be run after setup
   void run();

   //The method which runs the game loop - called from within run
   void game_loop( Field& field );
};

#endif

