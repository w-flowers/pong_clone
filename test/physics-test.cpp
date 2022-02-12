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

      struct positiond pos1 = {0 , 0};

      struct positiond pos2 = {1 , 0};

      struct positiond pos3 = {0 , 1};

      struct positiond pos4 = {2 , 2};

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

      CHECK( approx_equal_anglesd( Physics::sqrd_dist_pt_ln( pos1, y_eq_2x1 ), 0.2) );

      CHECK( approx_equal_anglesd( Physics::sqrd_dist_pt_ln( pos2, y_eq_2x1 ), 1.8) );

      CHECK( Physics::sqrd_dist_pt_ln( pos3, y_eq_2x1 ) == 0.0);

      CHECK( approx_equal_anglesd( Physics::sqrd_dist_pt_ln( pos4, y_eq_2x1 ), 1.8) );
   }

   Ball ball{ 10, 40.0, 40.0, 10.0 };

   struct position pos1 {40, 60};

   struct position pos2 {40, 21};

   SECTION( "Ball bounces correctly off horizontal line while moving vertically." )
   {
      ball.move();

      if( Physics::is_colliding_bp( ball, pos1 ) )
      {
         Physics::collide_ball_point( ball, pos1 );
      }

      if( Physics::is_colliding_bp( ball, pos2 ) )
      {
         Physics::collide_ball_point( ball, pos2 ); //should do nothing
      }

      REQUIRE_THAT( ball.get_position().x,
                    Catch::Matchers::WithinRel( 40.0, 0.0001 ) );

      REQUIRE_THAT( ball.get_position().y,
                    Catch::Matchers::WithinRel( 50.0, 0.0001 ) );

      ball.move();

      REQUIRE_THAT( ball.get_position().x,
                    Catch::Matchers::WithinRel( 40.0, 0.0001 ) );

      REQUIRE_THAT( ball.get_position().y,
                    Catch::Matchers::WithinRel( 40.0, 0.0001 ) );

      ball.move();

      if( Physics::is_colliding_bp( ball, pos1 ) )
      {
         Physics::collide_ball_point( ball, pos1 );//should do nothing
      }

      if( Physics::is_colliding_bp( ball, pos2 ) )
      {
         Physics::collide_ball_point( ball, pos2 ); 
      }

      ball.move();

      REQUIRE_THAT( ball.get_position().x,
                    Catch::Matchers::WithinRel( 40.0, 0.0001 ) );

      REQUIRE_THAT( ball.get_position().y,
                    Catch::Matchers::WithinRel( 40.0, 0.1 ) );
   }

   SECTION( "Ball moving vertically bounces correctly off pi/4 angled line" )
   {
      ball.bounce( this_pi / 4.0 );

      ball.move();

      CAPTURE( ball.get_position().x );

      CAPTURE( ball.get_position().y );

      CAPTURE( ball.get_velocity().dx );

      CAPTURE( ball.get_velocity().dy );

      REQUIRE_THAT( ball.get_position().x,
                    Catch::Matchers::WithinRel( 50.0, 0.0001 ) );

      REQUIRE_THAT( ball.get_position().y,
                    Catch::Matchers::WithinRel( 40.0, 0.0001 ) );

      SECTION( "Ball moving horizontally bounces correctly off pi/4 angled line" )
      {
         ball.bounce( this_pi / 4.0 );

         if( Physics::is_colliding_bp( ball, pos2 ) )
         {
            Physics::collide_ball_point( ball, pos2 ); //should do nothing
         }

         ball.move();

         REQUIRE_THAT( ball.get_position().x,
               Catch::Matchers::WithinRel( 50.0, 0.0001 ) );

         REQUIRE_THAT( ball.get_position().y,
               Catch::Matchers::WithinRel( 50.0, 0.0001 ) );

     }

      SECTION( "Ball moving horizontally bounces correctly off vertical line" )
      {
         ball.bounce( this_pi / 2.0 );

         ball.move();

         REQUIRE_THAT( ball.get_position().x,
               Catch::Matchers::WithinRel( 40.0, 0.0001 ) );

         REQUIRE_THAT( ball.get_position().y,
               Catch::Matchers::WithinRel( 40.0, 0.0001 ) );

         ball.move();

         ball.bounce( this_pi / 2.0 );

         ball.move();

         REQUIRE_THAT( ball.get_position().x,
               Catch::Matchers::WithinRel( 40.0, 0.0001 ) );

         REQUIRE_THAT( ball.get_position().y,
               Catch::Matchers::WithinRel( 40.0, 0.0001 ) );
      }
   }
}

