
/********************************************************************************
* Pong Clone - Physics (physics.hpp) 
*
* File containing the functions and classes making up the physics engine. To be
* populated in order to better seperate concerns in base classes and enable
* implementation of better algorithms. Manages all collision code between 
* objects.
*
* Author: William Flowers
********************************************************************************/

#ifndef PHYSICS

#define PHYSICS

#include "pong_clone_base.hpp"

#include "ball.hpp"

#include "line.hpp"

#include "boundary.hpp"

#include "field.hpp"

// Grid to store a vector of balls, lines and paddles for each grid square
// Collide function will then only be called on the objects in the same
// squares.
//
// Class divides field up into a grid of rows and columns specified in the
// constructor arguments.
class Field_Grid
{
public:
   //Need to add paddles to this structure
   Field_Grid( const Field& field, int rows, int columns );

   // This function assumes the rows/cols in grid are larger than the balls'
   // diameter
   void assign_ball_to_squares( const Ball& ball );

   void assign_line_to_squares( const Line& line );

   void return_objects_to_collide( 
         std::unordered_map< Ball*, std::set< Ball* > >& balls_to_collide,
         std::unordered_map< Ball*, std::set< Line_Object* > >& lines_to_collide
         );

private:
   int num_rows;

   int num_cols;

   std::vector<Field_Square> field_sqrs;
};

struct Field_Square
{
   std::vector<Ball *> balls {};

   std::vector<Line_Object *> edges {};

   std::vector<Line_Object *> paddles {};

   //top left corner of square
   struct position pos;

   //width
   int w;

   //height
   int h;
};


namespace Physics
{
   // Detect collisions and take appropriate action
   void detect_collisions( Field field );

   // NOTICE - Also exists in Ball class - will likely go back there, as ball
   // is responsible for its own movement
   //
   // Changes the internal dx and dy components of velocity according to its
   // angle and the angle of the line/object it bounces off
   // NOTE: edge_angle and vel_angle() CANNOT be equal - clipping will occur
   // Controlling function needs to ensure that edge_angle != vel_angle()
   void bounce( Ball& ball, float edge_angle );

   //Check collision and then collide a ball off a point
   void collide_ball_point( Ball& ball, struct position pos );

   //Check collision between a ball and a line, excluding endpoints
   bool is_colliding_bl( Ball& ball, const Line& line );

   //Check then execute collision between a ball and a line
   void collide_ball_line( Ball& ball, const Line_Object& line_o );

   //Check then execute collision between a ball and a ball
   void collide_balls( Ball& ball1, Ball& ball2 );

   // Gives equation of line in form a(x - p.x) + b(y - p.y) = 0
   struct Line_Eq
   {
      float a;

      float b;

      struct positionf p;
   };

   // Compute square of distance between point and line
   float sqrd_dist_pt_ln( struct positionf pos, Line_Eq line );
};

#endif

