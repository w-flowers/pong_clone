
/******************************************************************************
 * Paddle (paddle.cpp)
 *
 * Class describing the paddles used by players of the game. All units measured
 * in an integer number of pixels.
 *
 * Author: William Flowers
 * ***************************************************************************/

#include "../inc/paddle.hpp"

Paddle::Paddle(int width_, int thickness_, int hori, int vert, int pos_max_, int pos_min_)
{
   width = width_;
   
   thickness = thickness_;
   
   position.x = hori;
   
   position.y = vert;
   
   pos_max = pos_max_;
   
   pos_min = pos_min_;
   
   angle = 0.0; //Paddle initialised as horizontal
   
   angle_d = this_pi / 60.0; //Paddle initialised with rate of change of 1/60 pi per frame
   
   speed = 4;
   
   if(!valid()) throw InvalidPaddle{};
}

bool Paddle::valid()
{
   return ( width >= 4 &&
      thickness >= 1 &&
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
   if( angle - angle_d > -this_pi/2 ) angle -= angle_d ;

   else angle = -this_pi/2;
}

void Paddle::expand_angle()
{
   if( angle + angle_d < this_pi/2 ) angle += angle_d ;

   else angle = this_pi/2 ;
}

void Paddle::set_speed( int speed_ )
{ 
   if( speed_ <= 0 || speed_ > ( ( pos_max - pos_min ) / 2) ) throw InvalidPaddle{};

   else speed = speed_ ; 
}

float Paddle::get_angle()
{
   return angle;
}

int Paddle::get_width()
{
   return width;
}

int Paddle::get_thickness()
{
   return thickness;
}

int Paddle::get_hori_pos()
{
   return position.x;
}

int Paddle::get_vert_pos()
{
   return position.y;
}

