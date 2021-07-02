
/********************************************************************************
* Pong Clone - Physics (physics.cpp) 
*
* File containing the functions and classes making up the physics engine. To be
* populated in order to better seperate concerns in base classes and enable
* implementation of better algorithms.
*
* Author: William Flowers
********************************************************************************/

#include "../inc/physics.hpp"

void Physics::bounce( Ball& ball, double edge_angle )
{
      double newangle = 2 * edge_angle - ball.vel_angle();
      
      ball.set_velocity( 
            //x value
            ball.get_speed() * cosf( newangle ),

            //y value
            ball.get_speed() * sinf( newangle )
            );
      
      return;
}

void Physics::collide_ball_point( Ball& ball, struct position pos )
{
   double dx = ball.get_position().x - static_cast<double>( pos.x );

   double dy = ball.get_position().y - static_cast<double>( pos.y );

   double b_to_p_angle = atan2( dy, dx );

   double new_dx = ball.get_radius() * cos( b_to_p_angle );

   double new_dy = ball.get_radius() * sin( b_to_p_angle );

//   ball.move_back();

   ball.bounce( 
         ( atan2( dy, dx )
           + this_pi / 2.0 ) 
         );

   ball.set_position(
         ( static_cast<double>( pos.x ) + 
           ( ( dx > 0 ) - ( dx < 0 ) ) * abs( new_dx ) ) ,
         ( static_cast<double>( pos.y ) + 
           ( ( dy > 0 ) - ( dy < 0 ) ) * abs( new_dy ) )
         );
}

bool Physics::is_colliding_bp( Ball& ball, struct position pos )
{
   double dx = ball.get_position().x - static_cast<double>( pos.x );

   double dy = ball.get_position().y - static_cast<double>( pos.y );

   int br = ball.get_radius();

   return ( square_d( dy ) + square_d( dx ) <= 
         static_cast<double>( br * br ) );
}

bool Physics::is_colliding_bl( Ball& ball, const Line& line )
{
   struct positiond curr_pos { ball.get_position().x, ball.get_position().y };

   double x1 = static_cast<double>( line.get_p1().x );

   double x2 = static_cast<double>( line.get_p2().x );

   double y1 = static_cast<double>( line.get_p1().y );

   double y2 = static_cast<double>( line.get_p2().y );

   Line_Eq l_e { (y2 - y1), ( -(x2 - x1) ), {x1, y1} };

   //check if within radius of line
   if( sqrd_dist_pt_ln( curr_pos, l_e ) <=
         square_d( (double) ball.get_radius() ) )
   {
      double xm = ( x1 + x2 ) / 2.0;

      double ym = ( y1 + y2 ) / 2.0;

      //normal equation at midpoint of line
      Line_Eq n_e { ( x2 - x1 ), ( y2 - y1 ), {xm, ym} };

      return ( sqrd_dist_pt_ln( curr_pos, n_e ) <=
            square_d( ym - y1 ) + square_d( xm - x1 ) );
   }

   else return false;
}

void Physics::collide_ball_line( Ball& ball, const Line_Object& line_o,
     int index, std::vector< std::set< struct position > >& points_to_collide 
     )
{
   if( is_colliding_bl( ball, line_o.line ) )
   {
      switch( line_o.get_type() )
      {
         case edge:
            {
               double normal_angle = line_o.line.get_line_angle() + this_pi/2;

               double x1 = static_cast<double>( line_o.line.get_p1().x );

               double x2 = static_cast<double>( line_o.line.get_p2().x );

               double y1 = static_cast<double>( line_o.line.get_p1().y );

               double y2 = static_cast<double>( line_o.line.get_p2().y );

               Line_Eq l_e { (y2 - y1), ( -(x2 - x1) ), {x1, y1} };

               double dist = sqrt( sqrd_dist_pt_ln( ball.get_position(), l_e ) );

               double dx = dist * cos( normal_angle );

               double dy = dist * sin( normal_angle );

               double new_dx = ball.get_radius() * cos( normal_angle );

               double new_dy = ball.get_radius() * sin( normal_angle );

               double shift_x = new_dx - dx;

               double shift_y = new_dy - dy;

               ball.set_position( ball.get_position().x + shift_x,
                     ball.get_position().y + shift_y );

               //ball.move_back();

               ball.bounce( line_o.line.get_line_angle() );

               break;
            }
         case goal:

            //Insert goal code here
            break;

         case paddle:

            //Insert paddle code here
            break;
      }
   }
   else 
   {
      struct position p1 = line_o.line.get_p1();

      if( is_colliding_bp( ball, p1 ) ) 
      {
         points_to_collide[index].insert( { p1 } );
      }

      struct position p2 = line_o.line.get_p2();

      if( is_colliding_bp( ball, p2 ) )
      {
         points_to_collide[index].insert( { p2 } );
      }
   }
}

void Physics::collide_balls( Ball& ball1, Ball& ball2 )
{
   double dy = ball1.get_position().y - ball2.get_position().y;

   double dx = ball1.get_position().x - ball2.get_position().x;

   if( square_d( dx ) + square_d( dy ) <=
         static_cast<double>( 
            square_int( ball1.get_radius() + ball2.get_radius() ) )
     )
   {
      // Move balls so that they are no longer clipping
      double line_centres_a = atan2( dy, dx );

      double new_dx = 
         ( ball1.get_radius() + ball2.get_radius() ) * cos( line_centres_a );

      double new_dy = 
         ( ball1.get_radius() + ball2.get_radius() ) * sin( line_centres_a );

      double b1x = ball1.get_position().x;
      double b1y = ball1.get_position().y;
      double b2x = ball2.get_position().x;
      double b2y = ball2.get_position().y;

      double v1x = ball1.get_velocity().dx;
      double v1y = ball1.get_velocity().dy;
      double v2x = ball2.get_velocity().dx;
      double v2y = ball2.get_velocity().dy;

      positiond midpt = { ( b1x + b2x / 2 ), ( ( b1y + b2y ) / 2 ) };

      double x_shift = ( abs( new_dx ) - abs( dx ) ) / 2;

      double y_shift = ( abs( new_dy ) - abs( dy ) ) / 2;

      ball1.set_position(
           b1x + ( ( ( b1x - midpt.x ) > 0 ) - ( ( b1x - midpt.x ) < 0 ) ) * x_shift * 2,
           b1y + ( ( ( b1y - midpt.y ) > 0 ) - ( ( b1y - midpt.y ) < 0 ) ) * y_shift * 2);

      ball2.set_position(
           b2x + ( ( ( b2x - midpt.x ) > 0 ) - ( ( b2x - midpt.x ) < 0 ) ) * x_shift * 2,
           b2y + ( ( ( b2y - midpt.y ) > 0 ) - ( ( b2y - midpt.y ) < 0 ) ) * y_shift * 2);

      //bounce off perpendicular to line joining centres of b1 and b2
//      double normal_angle = line_centres_a + this_pi / 2.0; 

      //Bounce balls using algorithm for inelastic collision
      double v1f = 
         ( ( v1x - v2x ) * ( b1x - b2x ) + ( v1y - v2y ) * ( b1y - b2y ) );

      double v2f =
         ( ( v2x - v1x ) * ( b2x - b1x ) + ( v2y - v1y ) * ( b2y - b1y ) );

      double norm_x1_x2 = square_d( b1x - b2x ) + square_d( b1y - b2y );

      double norm_x2_x1 = square_d( b2x - b1x ) + square_d( b2y - b1y );

      ball1.set_velocity(
            v1x - ( v1f / norm_x1_x2 ) * ( b1x - b2x ),

            v1y - ( v1f / norm_x1_x2 ) * ( b1y - b2y )
            );

      ball2.set_velocity(
            v2x - ( v2f / norm_x2_x1 ) * ( b2x - b1x ),

            v2y - ( v2f / norm_x2_x1 ) * ( b2y - b1y )
            );

      /* Old algorithm
      //ball1.move_back();

      ball1.bounce( normal_angle );

      //ball2.move_back();

      ball2.bounce( normal_angle );
      */
   }
}

float Physics::sqrd_dist_pt_ln( struct positiond pos, Line_Eq line )
{
   double ax_by_c = line.a * ( pos.x - line.p.x ) + 
      line.b * ( pos.y - line.p.y );

   return square_d( ax_by_c ) / ( line.a*line.a + line.b*line.b );
}
