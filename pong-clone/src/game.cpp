
/********************************************************************************
* Pong Clone - Game (game.cpp) 
*
* A class that manages the running of the game as a whole. Contains the run
* method and the event loop.
*
* Author: William Flowers
********************************************************************************/

#include "../inc/game.hpp"


void Game::run()
{
   //insert body here

   game_loop();

   return;
}

void Game::game_loop()
{
   //insert body here
   
   //Render Boundaries

   //Render Ball
   
   //Draw scoreboards
   
   //
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
       //Move game objects
       
       //Render
   }
   
   return;
}

