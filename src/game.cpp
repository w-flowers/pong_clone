
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

   // Initialise field

   //game_loop( field );

   std::cout << "Please enter a game mode (local/net):\n";

   std::string input {""};

   std::cin >> input;

   if( input == "local" )
   {
      std::cout << "Test successful\n";

      //fork to run server

   }

   else
   {
      std::cout << "Functionality not implemented.\n";
   }

   return;
}

void Game::game_loop( Field& field )
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
       //gui.render_all( field );
   }
   
   return;
}

