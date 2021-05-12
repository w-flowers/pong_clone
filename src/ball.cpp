
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

Ball::Ball( int r, double init_x, double init_y, double speed )
   : radius{r}, velocity{0, speed, speed},
   position{init_x, init_y} 
{
   if( r <= 0 ) throw InvalidBall{};

   return;
}

void Ball::bounce( double edge_angle )
{
      double newangle = 2 * edge_angle - vel_angle();
      
      velocity.dy = velocity.speed * sinf( newangle );
      
      velocity.dx = velocity.speed * cosf( newangle );
      
      return;
}

void Ball::move()
{
   position.x += velocity.dx;

   position.y += velocity.dy;
}

void Ball::move_back()
{
   position.x -= velocity.dx;

   position.y -= velocity.dy;
}

struct positiond Ball::get_position() const
{
   return position;
}

void Ball::set_position( double x, double y )
{
   position.x = x;

   position.y = y;
}

double Ball::get_speed() const
{
   return velocity.speed;
}

struct velocity Ball::get_velocity() const
{
   return velocity;
}

void Ball::set_velocity( double dx, double dy )
{
   velocity.dx = dx;

   velocity.dy = dy;

   return;
}

int Ball::get_radius() const
{
   return radius;
}

double Ball::vel_angle()
{
   return atan2( velocity.dy, velocity.dx );
}

