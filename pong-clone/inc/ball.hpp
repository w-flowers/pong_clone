
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

class Ball
{
public:
   //Constructor - initialises ball with radius r, position given by inits,
   // and the speed going in the vertical positive direction
   Ball( int r, int init_x, int init_y, float speed );
   
   // Changes the internal dx and dy components of velocity according to its
   // angle and the angle of the line/object it bounces off
   void bounce( float edge_angle );

   // Moves the ball one step, according to what the internal dx and dy are
   void move();

   // Returns current position of the ball
   struct position get_position() const;

   // Returns the radius of the ball
   int get_radius() const;

private:
   
   int radius;
   
   struct velocity
   {
      int dx;
      
      int dy;
      
      float speed;
   } velocity;
   
   struct position position;
   
   class InvalidBall {};
   
   //calculate angle of balls movement from horizontal - range from +pi to -pi
   float vel_angle();
};

#endif

