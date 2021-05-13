
/******************************************************************************
 * Paddle (paddle.hpp)
 *
 * Class describing the paddles used by players of the game. All units measured
 * in an integer number of pixels.
 *
 * Author: William Flowers
 * ***************************************************************************/

#include "pong_clone_base.hpp"

#include "line.hpp"

class Paddle : public Line_Object
{
public:
   
   Paddle(int half_width, int hori, int vert, int pos_max, int pos_min,
         Player p);
   
   void move_right();
   
   void move_left();
   
   void shrink_angle();
   
   void expand_angle();
   
   void set_speed( int speed_ );
   
   int get_width();

   struct position get_position();
private:
   
   int half_width; //width of striking surface of the paddle, must be greater than 4, should be even

   struct position position; //coordinates of top centre of paddle on screen - must be greater than 0
   
   int pos_max; //max horizontal position, must be greater than 0
    
   int pos_min; //min horizontal position, must be greater than 0, pos_min
   
   /*
   For pos_max and pos_min, it is the caller's resposibility to ensure that they factor in the
   width and thickness of the paddle
   */
   
   float angle_d; //rate of change of angle
   
   int speed; //horizontal movement speed of paddle per frame - positive integer
   
   class InvalidPaddle {};
   
   bool valid();
};

