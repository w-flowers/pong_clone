
/********************************************************************************
* Pong Clone - Field (field.cpp) 
*
* DESCRIPTION
*
* Author: William Flowers
********************************************************************************/

#include "../inc/field.hpp"

Field::Field( std::vector<Line_start> boun_init_list,
      std::vector<BallArgs> ball_init_list, int x_d, int y_d ):
    boundary {boun_init_list}, x_dim {x_d}, y_dim {y_d}
{
   if( x_dim <= 0 || y_dim <= 0 )
   {
      throw InvalidDimensions{};
   }

   for( auto arg : ball_init_list )
   {
      ball_vec.emplace_back( Ball( arg.radius, arg.init_x, arg.init_y, arg.speed) );
   }
}

Ball Field::get_ball( int index )
{
   return ball_vec.at( index );
}

int Field::ball_vec_size()
{
   return ball_vec.size();
}

int Field::get_x_dim() const
{
   return x_dim;
}

int Field::get_y_dim() const
{
   return y_dim;
}

void Field::advance_field()
{
   for( Ball& b : ball_vec )
   {
      b.move();
   }
}

