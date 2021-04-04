/********************************************************************************
* Pong Clone - boundary (boundary.hpp) 
*
* A class to manage the boundary of the game. Stores a vector of the game and
* provides initialisation based on a list of points. Will always return a closed
* polygon.
*
* Author: William Flowers
********************************************************************************/
#include "../inc/boundary.hpp"

#include "catch.hpp"

TEST_CASE( "Boundary Class initialises correctly", "[Boundary]" )
{

   std::vector<Line_start> list {};

   list.reserve(20);

   for(int i = 1; i < 11; i++)
   {
      Line_start temp {{10*i, 10}, edge, none};

      list.push_back(temp);
   }

   for(int i = 10; i > 0; i--)
   {
      Line_start temp {{10*i, 20}, edge, none};

      list.push_back(temp);
   }

   Boundary test {list};

   REQUIRE( test.get_lines_size() == 20 );

   for(int i = 0; i < 9; i++)
   {
      REQUIRE( test.get_line(i).line.get_p1().x == 10*( i + 1 ) );

      REQUIRE( test.get_line(i).line.get_p1().y == 10 );

      REQUIRE( test.get_line(i).line.get_p2().x == 10*( i + 2 ) );

      REQUIRE( test.get_line(i).line.get_p2().y == 10 );
   }

   REQUIRE( test.get_line(9).line.get_p1().x == 10*10 );

   REQUIRE( test.get_line(9).line.get_p1().y == 10 );

   REQUIRE( test.get_line(9).line.get_p2().x == 10*10 );

   REQUIRE( test.get_line(9).line.get_p2().y == 20 );

   for(int i = 10; i < 19; i++)
   {
      REQUIRE( test.get_line(i).line.get_p1().x == 10*( 20 - i ) );

      REQUIRE( test.get_line(i).line.get_p1().y == 20 );

      REQUIRE( test.get_line(i).line.get_p2().x == 10*( 19 - i ) );

      REQUIRE( test.get_line(i).line.get_p2().y == 20 );
   }

   REQUIRE( test.get_line(19).line.get_p1().x == 10 );

   REQUIRE( test.get_line(19).line.get_p1().y == 20 );

   REQUIRE( test.get_line(19).line.get_p2().x == 10 );

   REQUIRE( test.get_line(19).line.get_p2().y == 10 );
}

