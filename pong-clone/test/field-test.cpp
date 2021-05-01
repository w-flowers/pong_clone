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
      Line_start temp {{900*i, 1000*( i%2 )}, edge, none};

      list.push_back(temp);
   }

   for(int i = 10; i > 0; i--)
   {
      Line_start temp {{900*i, 6000 - 1000 * ( i%2 ) }, edge, none};

      list.push_back(temp);
   }

   std::vector<BallArgs> ball_init;

   ball_init.reserve(6);

   for(int i = 0; i < 6; i++)
   {
      BallArgs temp {200, 1200*( i + 1 ), 3000, 20};

      ball_init.push_back( temp );
   }

   Field test_field {list, ball_init, 10000, 8000, 20, 20};

   REQUIRE( test_field.get_x_dim() == 10000 );

   REQUIRE( test_field.get_y_dim() == 8000 );

   for(int i = 0; i < test_field.ball_vec_size(); i++)
   {
      REQUIRE( test_field.get_ball(i).get_position().x == 1200*( i + 1 ) );

      REQUIRE( test_field.get_ball(i).get_position().y == 3000 );

      REQUIRE( test_field.get_ball(i).get_radius() == 200 );

      REQUIRE( test_field.get_ball(i).get_speed() == 20 );
   }

   test_field.advance_field();

   for(int i = 0; i < test_field.ball_vec_size(); i++)
   {
      REQUIRE( test_field.get_ball(i).get_position().x == 1200*( i + 1 ) );

      REQUIRE( test_field.get_ball(i).get_position().y == 3020 );

      REQUIRE( test_field.get_ball(i).get_radius() == 200 );

      REQUIRE( test_field.get_ball(i).get_speed() == 20 );
   }

   SECTION( "Balls do not leave boundaries of field over time" )
   {
      for( int i = 0; i < 5000; i++ )
      {
         test_field.advance_field();
      }

      for(int i = 0; i < test_field.ball_vec_size(); i++)
      {
         CAPTURE( i );

         CHECK( test_field.get_ball(i).get_position().x <= 10000 );

         CHECK( test_field.get_ball(i).get_position().y <= 8000 );

         CHECK( test_field.get_ball(i).get_position().x >= 0 );

         CHECK( test_field.get_ball(i).get_position().y >= 0 );
      }
   }
}

