
/********************************************************************************
* Pong Clone - Field (field.hpp) 
*
* Class that manages the field - specifically, the ball(s), boundaries and
* paddles.
*
* Author: William Flowers
********************************************************************************/

#ifndef FIELD_HPP

#define FIELD_HPP

//NOTE: Some of these includes are redundant, they are simply here to show
//dependencies and defend against future implementation changes

#include "pong_clone_base.hpp"

#include "ball.hpp"

#include "line.hpp"

#include "paddle.hpp"

#include "boundary.hpp"

class Field
{
public:
   Field( std::vector<Line_start> init_list, int ball_radius );

   Boundary get_boundary();

   Ball get_ball( int index );

   int ball_vec_size();

   //TO DO: Paddle Methods
   
   //moves elements in field by one step
   void advance_field();
private:
   Boundary boundary;

   std::vector<Ball> ball_vec;

   //TO DO: std::vector<Paddle> paddles;
};

#endif

