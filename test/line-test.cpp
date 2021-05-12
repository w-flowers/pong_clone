
/******************************************************************************
 * Pong-clone - Line (line-test.cpp)
 *
 * All units an integer number of pixels. Line angle calculated according to 
 * a number plane where the positive direction is right and down, negative left
 * and up. All lines defined herein may be rendered by the program.
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

   SECTION( "Set functions work correctly" )
   {
      newline.set_p1( 3, 4 );

      REQUIRE( newline.get_p1().x == 3 );

      REQUIRE( newline.get_p1().y == 4 );

      REQUIRE( newline.get_p2().x == 1 );

      REQUIRE( newline.get_p2().y == 1 );

      newline.set_p2( 5, 6 );

      REQUIRE( newline.get_p1().x == 3 );

      REQUIRE( newline.get_p1().y == 4 );

      REQUIRE( newline.get_p2().x == 5 );

      REQUIRE( newline.get_p2().y == 6 );
   }
}


TEST_CASE( "Line class computes angles correctly", "[LineAngle]" )
{
   struct position p1_ = { 0, 0 };

   struct position p2_ = { 1, 1 };

   struct position p3_ = { 0, 1 };

   struct position p4_ = { 1, 0 };

   Line col1 { p1_, p2_ };

   Line col2 { p1_, p3_ };

   Line col3 { p1_, p4_ };

   Line col4 { p2_, p3_ };

   Line col5 { p2_, p4_ };

   Line col6 { p3_, p4_ };

   SECTION( "Angles are computed correctly" )
   {
      REQUIRE( approx_equal_anglesd( col1.get_line_angle(), this_pi / 4.0 ) );

      REQUIRE( approx_equal_anglesd( col2.get_line_angle(), this_pi / 2.0 ) );

      REQUIRE( approx_equal_anglesd( col3.get_line_angle(), 0.0 ) );

      REQUIRE( approx_equal_anglesd( col4.get_line_angle(), this_pi ) );

      REQUIRE( approx_equal_anglesd( col5.get_line_angle(), - ( this_pi / 2.0 ) ) );

      REQUIRE( approx_equal_anglesd( col6.get_line_angle(), - ( this_pi / 4.0 ) ) );
   }
}

