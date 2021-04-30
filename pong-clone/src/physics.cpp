
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

void Physics::bounce( Ball& ball, float edge_angle )
{
      float newangle = 2 * edge_angle - ball.vel_angle();
      
      ball.set_velocity( 
            //x value
            static_cast<int>( lroundf( ball.get_speed() * cosf( newangle ) ) ),

            //y value
            static_cast<int>( lroundf( ball.get_speed() * sinf( newangle ) ) )
            );
      
      return;
}

void Physics::collide_ball_point( Ball& ball, struct position pos )
{
   int dx = ball.get_position().x - pos.x;

   int dy = ball.get_position().y - pos.y;

   ball.bounce( 
         ( atan2f( static_cast<float>( dy ), static_cast<float>( dx ) )
           + this_pi / 2.0 ) 
         );
}

bool Physics::is_colliding_bp( Ball& ball, struct position pos )
{
   int dx = ball.get_position().x - pos.x;

   int dy = ball.get_position().y - pos.y;

   int br = ball.get_radius();

   return ( square_int( dy ) + square_int( dx ) <= br * br );
}

bool Physics::is_colliding_bl( Ball& ball, const Line& line )
{
   struct positionf curr_pos { static_cast<float>( ball.get_position().x ), 
      static_cast<float>( ball.get_position().y ) };

   int x1 = line.get_p1().x;

   int x2 = line.get_p2().x;

   int y1 = line.get_p1().y;

   int y2 = line.get_p2().y;

   Line_Eq l_e { (y2 - y1), ( -(x2 - x1) ), {x1, y1} };

   //check if within radius of line
   if( sqrd_dist_pt_ln( curr_pos, l_e ) <=
         square_float( (float) ball.get_radius() ) )
   {
      float xm = ( x1 + x2 ) / 2.0;

      float ym = ( y1 + y2 ) / 2.0;

      //normal equation at midpoint of line
      Line_Eq n_e { ( x2 - x1 ), ( y2 - y1 ), {xm, ym} };

      return ( sqrd_dist_pt_ln( curr_pos, n_e ) <=
            square_float( ym - y1 ) + square_float( xm - x1 ) );
   }

   else return false;
}

void Physics::collide_ball_line( Ball& ball, const Line_Object& line_o,
     std::unordered_map< Ball*, std::set< struct position > >& points_to_collide 
     )
{
   if( is_colliding_bl( ball, line_o.line ) )
   {
      switch( line_o.get_type() )
      {
         case edge:

            ball.bounce( line_o.line.get_line_angle() );
            
            break;

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
         points_to_collide.at( &ball ).insert( { p1 } );
      }

      struct position p2 = line_o.line.get_p2();

      if( is_colliding_bp( ball, p2 ) )
      {
         points_to_collide.at( &ball ).insert( { p2 } );
      }
   }
}

void Physics::collide_balls( Ball& ball1, Ball& ball2 )
{
   int dy = ball1.get_position().y - ball2.get_position().y;

   int dx = ball1.get_position().x - ball2.get_position().x;

   if( square_int( dx ) + square_int( dy ) <=
         square_int( ball1.get_radius() + ball2.get_radius() ) )
   {
      //bounce off perpendicular to line joining centres of b1 and b2
      float normal_angle = 
         ( atan2f( static_cast<float>( dy ), static_cast<float>( dx ) )
           + this_pi / 2.0 ); 

      ball1.bounce( normal_angle );

      ball2.bounce( normal_angle );
   }
}

float Physics::sqrd_dist_pt_ln( struct positionf pos, Line_Eq line )
{
   float ax_by_c = line.a * ( pos.x - line.p.x ) + 
      line.b * ( pos.y - line.p.y );

   return square_float( ax_by_c ) / ( line.a*line.a + line.b*line.b );
}
