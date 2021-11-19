
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
   std::vector< int > balls {};

   std::vector< int > edges {};

   std::vector< int > paddles {};

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
   void assign_ball_to_squares( Ball& ball, int index );

   // Version of the function above which assigns ball to all squares
   // for which both the row and column contain a point in the ball.
   void assign_ball_to_squares_lazy( Ball& ball, int index );

   bool point_in_square( struct positiond p, Field_Square& f );

   bool point_in_column( struct positiond p, int col );

   bool point_in_row( struct positiond p, int row );

   void find_squares_of_point( struct positiond p, 
         std::vector<int>& indexes );

   // Puts line in all field squares in which the line is in contact with the
   // interior of said square, or the bottom/right boundary, or the field edge.
   void assign_line_to_squares( Line_Object& line, int index );

   // Deletes all elements of the Ball* vectors
   void clear_balls();

   // Takes a reference to a maps of Balls to a sets of objects to collide with.
   void return_objects_to_collide( 
         std::vector< std::set< int > >& balls_to_collide,
         std::vector< std::set< int > >& lines_to_collide,
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
   Field( const std::vector<Line_start>& boun_init_list, 
         const std::vector<BallArgs>& ball_init_list, int x_d, int y_d, 
         int rows, int columns);

   //public - encapsulation in boundary class
   Boundary boundary;

   std::optional<Paddle> paddle_1 {};

   std::optional<Paddle> paddle_2 {};

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

   // I am going to make a version of this code that uses vectors and the index 
   // from the original ball vector instead, and measure its impact on performance.
   // With the current unordered map, 162 balls makes the pc run at about 40% 
   // or so.
   /*
   std::unordered_map< Ball*, std::set< Ball* > > balls_to_collide;

   std::unordered_map< Ball*, std::set< Line_Object* > > lines_to_collide;

   std::unordered_map< Ball*, std::set< struct position > > 
      points_to_collide;
   */

   // These vectors store the indexes of the balls and lines in their
   // containers in sets, one set for each ball index in ball_vec
   std::vector< std::set< int > > balls_to_collide;

   std::vector< std::set< int > > lines_to_collide;

   std::vector< std::set< struct position > > points_to_collide;
   
   //Dimensions of the field in total
   int x_dim;

   int y_dim;
   //TO DO: std::vector<Paddle> paddles;

   Field_Grid field_grid;
};

#endif

