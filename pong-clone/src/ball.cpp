
/********************************************************************************
* Pong Clone - Ball (ball.hpp) 
*
* Class describing the game ball. All units measured in an integer number of 
* pixels.
*
* NOTE: Currently ties movement to framerate. May be modified to implement frame
* independent movement.
*
* Author: William Flowers
********************************************************************************/

#include <../inc/ball.hpp>

Ball::Ball( int r )
{
   if( r <= 0 ) throw InvalidBall{};
   radius = r;

   velocity.dx = DEFDX;

   velocity.dy = DEFDY;

   velocity.speed = DEFSPD;

   position.x = DEFX;

   position.y = DEFY;

   return;
}

void Ball::bounce( float edge_angle )
{
      float newangle = 2 * edge_angle - vel_angle();
      
      velocity.dy = (int) lroundf( velocity.speed * sinf( newangle ) );
      
      velocity.dx = (int) lroundf( velocity.speed * cosf( newangle ) );
      
      return;
}

void Ball::move()
{
   position.x += velocity.dx;

   position.y += velocity.dy;
}

void Ball::render(SDL_Renderer *)
{

}

float Ball::vel_angle()
{
   return atan2f( ( (float) dy), ( (float) dx) );
}

