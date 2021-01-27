
/******************************************************************************
 * Pong-clone - Line (line.hpp)
 *
 * All units an integer number of pixels. Line angle calculated according to 
 * a number plane where the positive direction is right and down, negative left
 * and up. All lines defined herein may be rendered by the program.
 *
 * The lines defined in this class may be part of the subclass "Collidable".
 * This class manages collisions between Balls and Lines.
 *
 * Author: William Flowers
 * ***************************************************************************/

#include "../inc/line.hpp"

#include "catch.hpp"

TEST_CASE( "Line Class initialises correctly", "[line]" )
{
   struct position p1_ = { 0, 0 };

   struct position p2_ = { 1, 1 };

   Line newline { p1_, p2_ };

   REQUIRE( newline.get_p1().x == 0 );
   
   REQUIRE( newline.get_p1().y == 0 );

   REQUIRE( newline.get_p2().x == 1 );

   REQUIRE( newline.get_p2().y == 1 );
}

