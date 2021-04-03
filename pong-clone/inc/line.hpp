
/******************************************************************************
 * Pong-clone - Line (line.hpp)
 *
 * All units an integer number of pixels. Line angle calculated according to 
 * a number plane where the positive direction is right and down, negative left
 * and up. All lines defined herein may be rendered by the program.
 *
 * The lines defined in this class may be part of the subclass "Collidable".
 * This class manages collisions between Balls and Lines. For simplicity, it
 * assumes that there is only one ball radius.
 *
 * Author: William Flowers
 * ***************************************************************************/

#include "pong_clone_base.hpp"

#include "ball.hpp"

class Line
{
public:

   Line( struct position p1_ , struct position p2_ );

   struct position get_p1() const;

   struct position get_p2() const;

   ~Line();
private:
   struct position p1;

   struct position p2;
};

// Class for handling collision between balls and lines
class Collidable : public Line
{
public:
   Collidable( struct position p1_ , struct position p2_ , int br /*ball radius*/ );

   virtual void collide( Ball& ) = 0 ;

   //used to eliminate squares far from ball
   bool in_outer_collision_box( const Ball& );

   //checks whether ball has collided with line in this frame
   bool is_colliding( const Ball& );

   //needed for ball bouncing methods and collision methods
   float get_line_angle();

   //resize collision boxes if ball radius changes, called in constructor
   void set_collision_boxes( int br );

   ~Collidable();
private:

   // Private variables to give location of the outer collision box
   // Outer collision box is used to determine whether to run the collision
   // function.
   position ocb_tl; //top left

   position ocb_br; //bottom right

   // Private variables to give location of the inner collision box - floats
   // Inner collision box is used to determine which type of collision check to
   // use. If it is in the icb, use distance between pt and line. If not, check
   // points distance from endpoint.
   positionf icb_tl; //top left

   positionf icb_br; //bottom right

   float line_angle;
};

class Edge : public Collidable
{
public:
   Edge( struct position p1_, struct position p2_, int br );

   void collide( Ball& );
   
   ~Edge();
};

class Goal : public Collidable
{
public:
   //insert methods related to players and scoring here
};

