
/******************************************************************************
 * Paddle (paddle.hpp)
 *
 * Class describing the paddles used by players of the game. All units measured
 * in an integer number of pixels.
 *
 * TO DO: This class needs a rewrite to fit better with the other classes
 * Specifically, should be rewritten to incorporate an edge and use enums
 * defined in pong clone base.
 *
 * Author: William Flowers
 * ***************************************************************************/

#include "pong_clone_base.hpp"

class Paddle{
   
public:
   
   Paddle(int width, int thickness, int hori, int vert, int pos_max, int pos_min);
   
   void move_right();
   
   void move_left();
   
   void shrink_angle();
   
   void expand_angle();
   
   void set_speed( int speed_ );
   
   float get_angle();
   
   int get_width();
   
   int get_thickness();
   
   int get_hori_pos();
   
   int get_vert_pos();
      
private:
   
   int width; //width of striking surface of the paddle, must be greater than 4, should be even

   int thickness; //thickness of non-striking surface of the paddle, must be greater than 0
   
   struct position position; //coordinates of top centre of paddle on screen - must be greater than 0
   
   int pos_max; //max horizontal position, must be greater than 0
    
   int pos_min; //min horizontal position, must be greater than 0, pos_min
   
   /*
   For pos_max and pos_min, it is the caller's resposibility to ensure that they factor in the
   width and thickness of the paddle
   */
   
   float angle; //angle of rightmost point of paddle from horizontal - range from -pi/2 to pi/2
   
   float angle_d; //rate of change of angle
   
   int speed; //horizontal movement speed of paddle per frame - positive integer
   
   class InvalidPaddle {};
   
   bool valid();
};

