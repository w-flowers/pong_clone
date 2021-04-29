
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

namespace Physics
{
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

   // Compute square of distance between point and line
   float sqrd_dist_pt_ln( struct positionf pos, Line_Eq line );
};

#endif

