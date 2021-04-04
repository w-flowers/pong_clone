
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

   REQUIRE( ball.get_speed() == 10.0 );

   SECTION( "Ball moves correctly" )
   {
      ball.move();

      REQUIRE( ball.get_radius() == 10 );

      REQUIRE( ball.get_position().x == 40 );

      REQUIRE( ball.get_position().y == 50 );
   }

   //Section needs to be moved to physics.hpp
    
   SECTION( "Ball bounces correctly off horizontal line while moving vertically." )
   {
      ball.move();

      ball.bounce( 0 );

      REQUIRE( ball.get_position().x == 40 );

      REQUIRE( ball.get_position().y == 50 );
   
      ball.move();

      REQUIRE( ball.get_position().x == 40 );

      REQUIRE( ball.get_position().y == 40 );

      ball.move();

      ball.bounce(0);

      ball.move();

      REQUIRE( ball.get_position().x == 40 );

      REQUIRE( ball.get_position().y == 40 );
   }

   SECTION( "Ball moving vertically bounces correctly off pi/4 angled line" )
   {
      ball.bounce( this_pi / 4.0 );

      ball.move();

      REQUIRE( ball.get_position().x == 50 );

      REQUIRE( ball.get_position().y == 40 );

      SECTION( "Ball moving horizontally bounces correctly off pi/4 angled line" )
      {
         ball.bounce( this_pi / 4.0 );

         ball.move();

         REQUIRE( ball.get_position().x == 50 );

         REQUIRE( ball.get_position().y == 50 );
      }

      SECTION( "Ball moving horizontally bounces correctly off vertical line" )
      {
         ball.bounce( this_pi / 2.0 );

         ball.move();

         REQUIRE( ball.get_position().x == 40 );

         REQUIRE( ball.get_position().y == 40 );
         
         ball.move();

         ball.bounce( this_pi / 2.0 );

         ball.move();

         REQUIRE( ball.get_position().x == 40 );

         REQUIRE( ball.get_position().y == 40 );
      }
   }
}

