
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

class Engine
{
public:
   // Detect collisions and take appropriate action
   void detect_collisions(Field field);

private:
   // Changes the internal dx and dy components of velocity according to its
   // angle and the angle of the line/object it bounces off
   // NOTE: edge_angle and vel_angle() CANNOT be equal - clipping will occur
   // Controlling function needs to ensure that edge_angle != vel_angle()
   void bounce(Ball& ball, float edge_angle);

   //Check collision and then collide a ball off a point
   void collide_ball_point( Ball& ball, struct position position );

   //Check collision between a ball and a line
   void is_colliding_bl( Ball& ball, Line& line );

   void collide_ball_edge( Ball& ball, Edge& edge );

   void collide_ball_goal( Ball& ball, Goal& goal );
};

#endif

