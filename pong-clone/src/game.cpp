
/********************************************************************************
* Pong Clone - Game (game.cpp) 
*
* A class that managers the running of the game as a whole. Contains the run
* method and the event loop.
*
* Author: William Flowers
********************************************************************************/

#include "../inc/game.hpp"

#define GUI_SIZE_X 500

#define GUI_SIZE_Y 500

void Game::run()
{
   //insert body here
   GUI gui { GUI_SIZE_X, GUI_SIZE_Y };

   game_loop();

   return;
}

void Game::game_loop()
{
   //insert body here
   SDL_Event e;

   bool quit = false;

   while ( !quit )
   {
       while ( SDL_PollEvent( &e ) )
       {
           if ( e.type == SDL_QUIT )
           {
               quit = true;
           }
       }
   }
   
   return;
}

