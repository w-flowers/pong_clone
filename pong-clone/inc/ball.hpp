
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

//Default ball values

#define DEFX 0

#define DEFY 0

#define DEFSPD 0

#define DEFDX 0

#define DEFDY 0


class Ball
{
public:
   
   Ball(int radius);
   
   void bounce(float edge_angle);

   void move();

   struct position get_position() const;

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

