
/********************************************************************************
* Pong Clone - Field (field.hpp) 
*
* Class that manages the field - specifically, the ball(s), boundaries and
* paddles. It manages movement but NOT collisions.
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

struct BallArgs
{
   int radius;

   int init_x;

   int init_y;

   float speed;
};

class Field
{
public:
   Field( std::vector<Line_start> boun_init_list, 
         std::vector<BallArgs> ball_init_list, int x_d, int y_d );

   //public - encapsulation in boundary class
   Boundary boundary;

   Ball get_ball( int index );

   int ball_vec_size();

   // Get dimensions of field
   int get_x_dim() const;

   int get_y_dim() const;

   //TO DO: Paddle Methods
   
   //moves elements in field by one step
   void advance_field();

   class InvalidDimensions{};
private:
   std::vector<Ball> ball_vec;

   std::unordered_map< Ball*, std::set< Ball* > > balls_to_collide;

   std::unordered_map< Ball*, std::set< Line_Object* > > lines_to_collide;

   //Dimensions of the field in total
   int x_dim;

   int y_dim;
   //TO DO: std::vector<Paddle> paddles;
};

#endif

