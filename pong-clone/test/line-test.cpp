
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


TEST_CASE( "Collidable Class initialises correctly", "[collidable]" )
{
   struct position p1_ = { 0, 0 };

   struct position p2_ = { 1, 1 };

   struct position p3_ = { 0, 1 };

   struct position p4_ = { 1, 0 };

   Edge col1 { p1_, p2_, 10 };

   Edge col2 { p1_, p3_, 10 };

   Edge col3 { p1_, p4_, 10 };

   Edge col4 { p2_, p3_, 10 };

   Edge col5 { p2_, p4_, 10 };

   Edge col6 { p3_, p4_, 10 };

   SECTION( "Angles are computed correctly" )
   {
      REQUIRE( approx_equal_anglesf( col1.get_line_angle(), this_pi / 4.0f ) );

      REQUIRE( approx_equal_anglesf( col2.get_line_angle(), this_pi / 2.0f ) );

      REQUIRE( approx_equal_anglesf( col3.get_line_angle(), 0.0f ) );

      REQUIRE( approx_equal_anglesf( col4.get_line_angle(), this_pi ) );

      REQUIRE( approx_equal_anglesf( col5.get_line_angle(), - ( this_pi / 2.0f ) ) );

      REQUIRE( approx_equal_anglesf( col6.get_line_angle(), - ( this_pi / 4.0f ) ) );
   }
}
