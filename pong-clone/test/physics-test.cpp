/******************************************************************************
 * Pong-clone - Physics (physics-test.cpp)
 *
 * Test of physics functions.
 *
 * Author: William Flowers
 * ***************************************************************************/

#include "../inc/physics.hpp"

#include "catch.hpp"

TEST_CASE( "Physics functions compile and work", "[physics]" )
{

   SECTION( "Correct calculation of square of distance between pt and line" )
   {
      Line_Eq hori_ln { 0.0, 1.0, {0.0, 3.0} };

      Line_Eq vert_ln { 1.0, 0.0, {3.0, 0.0} };

      Line_Eq y_eq_x { -1, 1, {0.0, 0.0} };

      Line_Eq y_eq_2x1 { -2, 1, {0.0, 1.0} };

      struct positionf pos1 = {0 , 0};

      struct positionf pos2 = {1 , 0};

      struct positionf pos3 = {0 , 1};

      struct positionf pos4 = {2 , 2};

      CHECK( Physics::sqrd_dist_pt_ln( pos1, hori_ln ) == 9.0);

      CHECK( Physics::sqrd_dist_pt_ln( pos2, hori_ln ) == 9.0);

      CHECK( Physics::sqrd_dist_pt_ln( pos3, hori_ln ) == 4.0);

      CHECK( Physics::sqrd_dist_pt_ln( pos4, hori_ln ) == 1.0);

      CHECK( Physics::sqrd_dist_pt_ln( pos1, vert_ln ) == 9.0);

      CHECK( Physics::sqrd_dist_pt_ln( pos2, vert_ln ) == 4.0);

      CHECK( Physics::sqrd_dist_pt_ln( pos3, vert_ln ) == 9.0);

      CHECK( Physics::sqrd_dist_pt_ln( pos4, vert_ln ) == 1.0);

      CHECK( Physics::sqrd_dist_pt_ln( pos1, y_eq_x ) == 0.0);

      CHECK( Physics::sqrd_dist_pt_ln( pos2, y_eq_x ) == 0.5);

      CHECK( Physics::sqrd_dist_pt_ln( pos3, y_eq_x ) == 0.5);

      CHECK( Physics::sqrd_dist_pt_ln( pos4, y_eq_x ) == 0.0);

      CHECK( approx_equal_anglesf( Physics::sqrd_dist_pt_ln( pos1, y_eq_2x1 ), 0.2) );

      CHECK( approx_equal_anglesf( Physics::sqrd_dist_pt_ln( pos2, y_eq_2x1 ), 1.8) );

      CHECK( Physics::sqrd_dist_pt_ln( pos3, y_eq_2x1 ) == 0.0);

      CHECK( approx_equal_anglesf( Physics::sqrd_dist_pt_ln( pos4, y_eq_2x1 ), 1.8) );
   }

   Ball ball{ 10, 40, 40, 10.0 };

   struct position pos1 {40, 55};

   struct position pos2 {40, 25};

   SECTION( "Ball bounces correctly off horizontal line while moving vertically." )
   {
      ball.move();

      Physics::collide_ball_point( ball, pos1 );

      Physics::collide_ball_point( ball, pos2 ); //should do nothing

      CHECK( ball.get_position().x == 40 );

      CHECK( ball.get_position().y == 50 );
   
      ball.move();

      CHECK( ball.get_position().x == 40 );

      CHECK( ball.get_position().y == 40 );

      ball.move();

      Physics::collide_ball_point( ball, pos1 );//should do nothing

      Physics::collide_ball_point( ball, pos2 );

      ball.move();

      CHECK( ball.get_position().x == 40 );

      CHECK( ball.get_position().y == 40 );
   }

   SECTION( "Ball moving vertically bounces correctly off pi/4 angled line" )
   {
      ball.bounce( this_pi / 4.0 );

      ball.move();

      CHECK( ball.get_position().x == 50 );

      CHECK( ball.get_position().y == 40 );

      SECTION( "Ball moving horizontally bounces correctly off pi/4 angled line" )
      {
         ball.bounce( this_pi / 4.0 );

         Physics::collide_ball_point( ball, pos2 ); //should do nothing

         ball.move();

         CHECK( ball.get_position().x == 50 );

         CHECK( ball.get_position().y == 50 );
      }

      SECTION( "Ball moving horizontally bounces correctly off vertical line" )
      {
         ball.bounce( this_pi / 2.0 );

         ball.move();

         CHECK( ball.get_position().x == 40 );

         CHECK( ball.get_position().y == 40 );
         
         ball.move();

         ball.bounce( this_pi / 2.0 );

         ball.move();

         CHECK( ball.get_position().x == 40 );

         CHECK( ball.get_position().y == 40 );
      }
   }
}

