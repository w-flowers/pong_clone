
/******************************************************************************
 * Pong-clone - Ball (ball-test.cpp)
 *
 * Author: William Flowers
 * ***************************************************************************/

#include "../inc/ball.hpp"

#include "catch.hpp"

TEST_CASE( "Ball Class initialises correctly", "[ball]" )
{
   Ball ball{ 10, 40, 40, 10.0 };

   REQUIRE( ball.get_radius() == 10 );

   REQUIRE( ball.get_position().x == 40 );

   REQUIRE( ball.get_position().y == 40 );

   SECTION( "Ball moves correctly" )
   {
      ball.move();

      REQUIRE( ball.get_radius() == 10 );

      REQUIRE( ball.get_position().x == 40 );

      REQUIRE( ball.get_position().y == 50 );
   }

   SECTION( "Ball bounces correctly off horizontal line." )
   {
      ball.move();

      ball.bounce( 0 );

      REQUIRE( ball.get_position().x == 40 );

      REQUIRE( ball.get_position().y == 50 );
   
      ball.move();

      REQUIRE( ball.get_position().x == 40 );

      REQUIRE( ball.get_position().y == 40 );
   }

}

