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

   std::vector<Line_Object_Args> list {};

   list.reserve(20);

   for(int i = 1; i < 10; i = i + 1)
   {
      Line_Object_Args temp {{900*i, 1000*( i%2 ) + 50 },
                             {900*(i+1), 1000*( (i+1)%2 ) + 50 },
                             edge,
                             none};

      list.push_back(temp);
   }

   Line_Object_Args side_1 {{900*(10), 1000*( ( 10 )%2 ) + 50 },
                            {900*10, 6000 - 1000 * ( 10 % 2 ) },
                            edge,
                            none};

   list.push_back( side_1 );

   for(int i = 10; i > 1; i = i - 1 )
   {
      Line_Object_Args temp {{900*i, 6000 - 1000 * ( i%2 ) },
                             {900*(i-1), 6000 - 1000 * ( (i-1)%2 ) },
                             edge,
                             none};

      list.push_back(temp);
   }


   Line_Object_Args side_2 {{900*(1), 6000 - 1000*( ( 1 )%2 ) },
                            {900*1, 1000 * ( 1 % 2 ) + 50 },
                            edge,
                            none};

   list.push_back( side_2 );

   std::vector<Ball_Args> ball_init;

   ball_init.reserve(6);

   for(int i = 0; i < 6; i++)
   {
      Ball_Args temp {25, 1200*( i + 1 ), 3000, 1.5};

      ball_init.push_back( temp );
   }

   struct Configuration config {sim, 10000, 8000, ball_init, list, 1, 1};

   Field test_field {config, 10, 10};

   REQUIRE( test_field.get_x_dim() == 10000 );

   REQUIRE( test_field.get_y_dim() == 8000 );

   for(int i = 0; i < test_field.ball_vec_size(); i++)
   {
      REQUIRE( test_field.get_ball(i).get_position().x == 1200*( i + 1 ) );

      REQUIRE( test_field.get_ball(i).get_position().y == 3000 );

      REQUIRE( test_field.get_ball(i).get_radius() == 25 );

      REQUIRE( test_field.get_ball(i).get_speed() == 1.5 );
   }

   test_field.advance_field();

   for(int i = 0; i < test_field.ball_vec_size(); i++)
   {
      REQUIRE( test_field.get_ball(i).get_position().x == 1200*( i + 1 ) );

      REQUIRE( test_field.get_ball(i).get_position().y == 3001.5 );

      REQUIRE( test_field.get_ball(i).get_radius() == 25 );

      REQUIRE( test_field.get_ball(i).get_speed() == 1.5 );
   }

   SECTION( "Balls do not leave boundaries of field over time" )
   {
      for( int i = 0; i < 25000; i++ )
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

