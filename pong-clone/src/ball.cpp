
/********************************************************************************
* Pong Clone - Ball (ball.cpp) 
*
* Class describing the game ball. All units measured in an integer number of 
* pixels.
*
* NOTE: Currently ties movement to framerate. May be modified to implement frame
* independent movement.
*
* Author: William Flowers
********************************************************************************/

#include "../inc/ball.hpp"

Ball::Ball( int r, int init_x, int init_y, float speed )
   : radius{r}, velocity{0, static_cast<int>( lroundf( speed ) ), speed},
   position{init_x, init_y} 
{
   if( r <= 0 ) throw InvalidBall{};

   return;
}

void Ball::bounce( float edge_angle )
{
      float newangle = 2 * edge_angle - vel_angle();
      
      velocity.dy = static_cast<int>( lroundf( velocity.speed * sinf( newangle ) ) );
      
      velocity.dx = static_cast<int>( lroundf( velocity.speed * cosf( newangle ) ) );
      
      return;
}

void Ball::move()
{
   position.x += velocity.dx;

   position.y += velocity.dy;
}

float Ball::vel_angle()
{
   return atan2f( ( static_cast<float>( velocity.dy ) ), ( static_cast<float>( velocity.dx ) ) );
}

struct position Ball::get_position() const
{
   return position;
}

int Ball::get_radius() const
{
   return radius;
}
