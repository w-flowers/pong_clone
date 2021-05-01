
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

#include "physics.hpp"

struct BallArgs
{
   int radius;

   double init_x;

   double init_y;

   double speed;
};


struct Field_Square
{
   std::vector< Ball * > balls {};

   std::vector< Line_Object * > edges {};

   std::vector< Line_Object * > paddles {};

   //top left corner of square
   struct position pos;

   //width
   int w;

   //height
   int h;
};

// Grid to store a vector of balls, lines and paddles for each grid square
// Collide function will then only be called on the objects in the same
// squares.
//
// Class divides field up into a grid of rows and columns specified in the
//   constructor arguments.
class Field_Grid
{
public:
   //Need to add paddles to this structure
   Field_Grid(  std::vector<Ball>& balls, Boundary& boundary, 
      int field_x_dim, int field_y_dim, int rows, int columns );

   //Empty Constructor
   Field_Grid() {};

   // This function assumes the rows/cols in grid are larger than the balls'
   // diameter
   //
   // Function gives all squares which a ball is in contact with.
   void assign_ball_to_squares( Ball& ball );

   // Puts line in all field squares in which the line is in contact with the
   // interior of said square, or the bottom/right boundary, or the field edge.
   void assign_line_to_squares( Line_Object& line );

   // Deletes all elements of the Ball* vectors
   void clear_balls();

   // Takes a reference to a maps of Balls to a sets of objects to collide with.
   void return_objects_to_collide( 
         std::unordered_map< Ball*, std::set< Ball* > >& balls_to_collide,
         std::unordered_map< Ball*, std::set< Line_Object* > >& lines_to_collide,
         std::vector< Ball >& ball_vec //Owner of Balls
         );

   //Function for testing purposes - defined in test/field-test.cpp
#ifdef PHYSICS_TEST
   Field_Square *get_field_square(int index);
#endif

private:
   int num_rows {0};

   int num_cols {0};

   std::vector<Field_Square> field_sqrs {};
};


class Field
{
public:
   Field( std::vector<Line_start> boun_init_list, 
         std::vector<BallArgs> ball_init_list, int x_d, int y_d, 
         int rows, int columns);

   //public - encapsulation in boundary class
   Boundary boundary;

   Ball& get_ball( int index );

   int ball_vec_size();

   // Get dimensions of field
   int get_x_dim() const;

   int get_y_dim() const;

   //TO DO: Paddle Methods
   
   //moves elements in field by one step
   void advance_field();

   class InvalidDimensions{};
private:
   // Implementation note: resizing or pushing back to this vector will
   // invalidate all the pointers to ball in all other structures - just don't!
   std::vector<Ball> ball_vec;

   std::unordered_map< Ball*, std::set< Ball* > > balls_to_collide;

   std::unordered_map< Ball*, std::set< Line_Object* > > lines_to_collide;

   std::unordered_map< Ball*, std::set< struct position > > 
      points_to_collide;

   //Dimensions of the field in total
   int x_dim;

   int y_dim;
   //TO DO: std::vector<Paddle> paddles;

   Field_Grid field_grid;
};

#endif

