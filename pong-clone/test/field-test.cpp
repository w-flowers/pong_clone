/********************************************************************************
* Pong Clone - field (field-test.cpp) 
*
* Test class for field
*
* Author: William Flowers
********************************************************************************/
#define PHYSICS_TEST

#include "../inc/field.hpp"

#include "catch.hpp"

Field_Square *Field_Grid::get_field_square(int index)
{
   return &field_sqrs.at(index);
}
   

TEST_CASE( "Field Class initialises correctly", "[Field]" )
{

   std::vector<Line_start> list {};

   list.reserve(20);

   for(int i = 1; i < 11; i++)
   {
      Line_start temp {{90*i, 100*( i%2 )}, edge, none};

      list.push_back(temp);
   }

   for(int i = 10; i > 0; i--)
   {
      Line_start temp {{90*i, 600 - 100 * ( i%2 ) }, edge, none};

      list.push_back(temp);
   }

   std::vector<BallArgs> ball_init;

   ball_init.reserve(6);

   for(int i = 0; i < 6; i++)
   {
      BallArgs temp {20, 100*i, 300, 2};

      ball_init.push_back( temp );
   }

   Field test_field {list, ball_init, 1000, 800, 10, 10};

   REQUIRE( test_field.get_x_dim() == 1000 );

   REQUIRE( test_field.get_y_dim() == 800 );

   for(int i = 0; i < test_field.ball_vec_size(); i++)
   {
      REQUIRE( test_field.get_ball(i).get_position().x == 100*i );

      REQUIRE( test_field.get_ball(i).get_position().y == 300 );

      REQUIRE( test_field.get_ball(i).get_radius() == 20 );

      REQUIRE( test_field.get_ball(i).get_speed() == 2 );
   }
   SECTION( "Balls and lines are in correct section of Field Grid")
   {

   }

   test_field.advance_field();

   for(int i = 0; i < test_field.ball_vec_size(); i++)
   {
      REQUIRE( test_field.get_ball(i).get_position().x == 100*i );

      REQUIRE( test_field.get_ball(i).get_position().y == 302 );

      REQUIRE( test_field.get_ball(i).get_radius() == 20 );

      REQUIRE( test_field.get_ball(i).get_speed() == 2 );
   }


}

