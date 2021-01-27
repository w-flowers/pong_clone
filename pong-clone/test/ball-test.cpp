
/******************************************************************************
 * Pong-clone - Ball (ball-test.cpp)
 *
 * Author: William Flowers
 * ***************************************************************************/

#include "../inc/ball.hpp"

#include "catch.hpp"

TEST_CASE( "Ball Class initialises correctly", "[ball]" )
{
   Ball ball{10};

   REQUIRE( ball.get_radius() == 10 );
}

