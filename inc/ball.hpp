
/********************************************************************************
* Pong Clone - Ball (ball.hpp) 
*
* Class describing the game ball. All units measured in an integer number of 
* pixels.
*
* NOTE: Currently ties movement to framerate. May be modified to implement frame
* independent movement.
*
* Author: William Flowers
********************************************************************************/

#ifndef BALL_HPP

#define BALL_HPP

#include "pong_clone_base.hpp"

struct velocity
{
   double dx;

   double dy;

   double speed;
};

class Ball
{
public:
   //Constructor - initialises ball with radius r, position given by inits,
   // and the speed going in the vertical positive direction
   Ball( int r, double init_x, double init_y, double speed );
   
   // Changes the internal dx and dy components of velocity according to its
   // angle and the angle of the line/object it bounces off
   // NOTE: edge_angle and vel_angle() CANNOT be equal - clipping will occur
   // Controlling function needs to ensure that edge_angle != vel_angle()
   void bounce( double edge_angle );

   // Moves the ball one step, according to what the internal dx and dy are
   void move();

   void move_back();

   // Returns current position of the ball
   struct positiond get_position() const;

   void set_position( double x, double y );

   double get_speed() const;

   struct velocity get_velocity() const;

   void set_velocity( double dx, double dy );

   // Returns the radius of the ball
   int get_radius() const;

   // calculate angle of balls movement from horizontal - range from +pi to -pi
   double vel_angle();

   // Reset ball to initial position and velocity
   void reset();

private:
   
   int radius;
   
   struct velocity velocity;
   
   const struct velocity init_vel;

   struct positiond position;
   
   const struct positiond init_pos;

   class InvalidBall {};
};

#endif

