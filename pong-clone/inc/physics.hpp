
/********************************************************************************
* Pong Clone - Physics (physics.hpp) 
*
* File containing the functions and classes making up the physics engine. To be
* populated in order to better seperate concerns in base classes and enable
* implementation of better algorithms.
*
* Author: William Flowers
********************************************************************************/

#ifndef PHYSICS

#define PHYSICS

// Grid to store a vector of balls, lines and paddles for each grid square
// Collide function will then only be called on the objects in the same
// squares.
class Field_Grid
{
   //Need to add paddles to this structure
   Field_Grid();
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
   void is_colliding_bl( Ball& ball, const Line& line );

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
   }

   // Compute square of distance between point and line
   float sqrd_dist_pt_ln( struct position pos, Line_Eq line );
};

#endif

