/******************************************************************************
 * Pong_clone - Game_Test (test/game_test.cpp)
 *
 * A test function to test the game class.
 *
 * Author: William Flowers
 * ***************************************************************************/

#include "../inc/game.hpp"

#include "catch.hpp"

TEST_CASE( "Game Class initilises correctly", "[game]" )
{
   Game main_game;

   SECTION( "Game method runs" )
   {
      main_game.run();
   }
}

