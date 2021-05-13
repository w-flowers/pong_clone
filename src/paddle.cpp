
/******************************************************************************
 * Paddle (paddle.cpp)
 *
 * Class describing the paddles used by players of the game. All units measured
 * in an integer number of pixels.
 *
 * Author: William Flowers
 * ***************************************************************************/

#include "../inc/paddle.hpp"

Paddle::Paddle(int width_, int hori, int vert, int pos_max_, int pos_min_,
      Player p):
   Line_Object( {hori + width_, vert}, {hori - width_, vert}, paddle, p ),
   half_width{width_}, position{hori, vert}, pos_max{pos_max_},
   pos_min{pos_min_}
{
   //Paddle initialised with rate of change of 1/60 pi per frame   
   angle_d = this_pi / 60.0; 
   
   speed = 4;
   
   if(!valid()) throw InvalidPaddle{};
}

bool Paddle::valid()
{
   return ( half_width >= 4 &&
      pos_max > 0 &&
      pos_min >= 0 &&
      pos_max - pos_min > 7 &&
      position.x <= pos_max &&
      position.x >= pos_min );
}

void Paddle::move_right()
{
   if( position.x + speed < pos_max ) position.x += speed ; 

   else position.x = pos_max ;
}

void Paddle::move_left()
{
   if( position.x - speed > pos_min ) position.x -= speed ;

   else position.x = pos_min ;
} 

void Paddle::shrink_angle()
{
   double angle = line.get_line_angle();

   if( angle - angle_d > -this_pi/2 ) angle -= angle_d ;

   else angle = -this_pi/2;

   line.set_p1( position.x + 
        static_cast<int>( round( cos( angle ) * half_width ) ),
        position.y + 
        static_cast<int>( round( sin( angle ) * half_width ) ) );

   line.set_p2( position.x - 
        static_cast<int>( round( cos( angle ) * half_width ) ),
        position.y - 
        static_cast<int>( round( sin( angle ) * half_width ) ) );
}

void Paddle::expand_angle()
{
   double angle = line.get_line_angle();

   if( angle + angle_d > this_pi/2 ) angle += angle_d ;

   else angle = this_pi/2;

   line.set_p1( position.x + 
        static_cast<int>( round( cos( angle ) * half_width ) ),
        position.y + 
        static_cast<int>( round( sin( angle ) * half_width ) ) );

   line.set_p2( position.x - 
        static_cast<int>( round( cos( angle ) * half_width ) ),
        position.y - 
        static_cast<int>( round( sin( angle ) * half_width ) ) );
}


void Paddle::set_speed( int speed_ )
{ 
   if( speed_ <= 0 || speed_ > ( ( pos_max - pos_min ) / 2) ) throw InvalidPaddle{};

   else speed = speed_ ; 
}

int Paddle::get_width()
{
   return 2*half_width;
}

struct position Paddle::get_position()
{
   return position;
}

