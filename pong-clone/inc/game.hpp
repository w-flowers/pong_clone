
/********************************************************************************
* Pong Clone - Game (game.hpp) 
*
* A class that managers the running of the game as a whole. Contains the run
* method and the event loop.
*
* Author: William Flowers
********************************************************************************/

#ifndef GAME_HPP

#define GAME_HPP

#include "gui.hpp"

class Game
{
public:
   //A containing method for all the game code, to be run after setup
   void run();

private:
   //The method which runs the game loop - called from within run
   void game_loop();
};

#endif

