
/******************************************************************************
 * Pong-clone - Line (line.hpp)
 *
 * All units an integer number of pixels. Line angle calculated according to 
 * a number plane where the positive direction is right and down, negative left
 * and up. All lines defined herein may be rendered by the program.
 *
 * The lines defined in this class may be part of the subclass "Collidable".
 * This class manages collisions between Balls and Lines.
 *
 * TO DO: 
 * Define the methods for collidable (outer rect - max of pts + radius, inner
 *  rect, use trig)
 * Move line angle from LINE to COLLIDABLE
 *
 * Author: William Flowers
 * ***************************************************************************/

#include "pong_clone_base.hpp"

#include "game_object.hpp"

#include "ball.hpp"

class Line : public Game_object
{
public:

   Line( int x1_, int y1_, int x2_, int y2_ );

   void render(SDL_Renderer *renderer){};

   void set_colour(SDL_Color colour);

private:

   int x1;

   int y1;

   int x2;

   int y2;

   SDL_Color line_colour {0, 0, 0, 0};
};

// Class for handling collision between balls and lines
class Collidable : public Line
{
public:
   Collidable();

   virtual void collide( Ball& ) = 0 ;

   bool in_collision_box( Ball& );

   bool is_colliding( Ball& );

   float get_line_angle();

private:

   //Private variables to give location of the outer collision box
   position ocb_tl; //top left

   position ocb_br; //bottom right

   //Private variables to give location of the inner collision box
   position icb_tl; //top left

   position icb_br; //bottom right

   float line_angle;
};

