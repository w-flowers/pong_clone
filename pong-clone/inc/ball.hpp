
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
   int dx;

   int dy;

   float speed;
};

class Ball
{
public:
   //Constructor - initialises ball with radius r, position given by inits,
   // and the speed going in the vertical positive direction
   Ball( int r, int init_x, int init_y, float speed );
   
   // DEPRECATED - look at physics.hpp instead
   // Changes the internal dx and dy components of velocity according to its
   // angle and the angle of the line/object it bounces off
   // NOTE: edge_angle and vel_angle() CANNOT be equal - clipping will occur
   // Controlling function needs to ensure that edge_angle != vel_angle()
   void bounce( float edge_angle );

   // Moves the ball one step, according to what the internal dx and dy are
   void move();

   // Returns current position of the ball
   struct position get_position() const;

   float get_speed() const;

   void set_velocity( int dx, int dy );

   // Returns the radius of the ball
   int get_radius() const;

   //calculate angle of balls movement from horizontal - range from +pi to -pi
   float vel_angle();
private:
   
   int radius;
   
   struct velocity velocity;
   
   struct position position;
   
   class InvalidBall {};
   
};

#endif

