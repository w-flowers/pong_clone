#include <cmath>

/********************************************************************************

Class describing the paddles used by players of the game

All units measured in an integer number of pixels

********************************************************************************/

const float this_pi = 3.141593; //local definition of pi, may change in future

class Paddle{
   
public:
   
   Paddle(int width, int thickness, int hori, int vert, int pos_max, int pos_min);
   
   void move_right()
   {
      if( position.hori + speed < pos_max ) position.hori += speed ; 
      
      else position.hori = pos_max ;
   } ;
   
   void move_left()
   {
      if( position.hori - speed > pos_min ) position.hori -= speed ;
      
      else position.hori = pos_min ;
   } ;
   
   void shrink_angle()
   {
      if( angle - angle_d > -this_pi/2 ) angle -= angle_d ;
      
      else angle = -this_pi/2;
   }
   
   void expand_angle()
   {
      if( angle + angle_d < this_pi/2 ) angle += angle_d ;
      
      else angle = this_pi/2 ;
   }
   
   void set_speed( int speed_ )
   { 
      if( speed_ <= 0 || speed_ > ( ( pos_max - pos_min ) / 2) ) throw InvalidPaddle{};
      
      else speed = speed_ ; 
   };
   
   float get_angle() { return angle; };
   
   int get_width() { return width; };
   
   int get_thickness() { return thickness; };
   
   int get_hori_pos() { return position.hori; };
   
   int get_vert_pos() { return position.vert; };
      
private:
   
   int width; //width of striking surface of the paddle, must be greater than 4, should be even
   
   int thickness; //thickness of non-striking surface of the paddle, must be greater than 0
   
   struct position 
      {
         int hori;
         int vert;
      } position; //coordinates of top centre of paddle on screen - must be greater than 0
   
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

Paddle::Paddle(int width_, int thickness_, int hori, int vert, int pos_max_, int pos_min_)
{
   width = width_;
   
   thickness = thickness_;
   
   position.hori = hori;
   
   position.vert = vert;
   
   pos_max = pos_max_;
   
   pos_min = pos_min_;
   
   angle = 0.0; //Paddle initialised as horizontal
   
   angle_d = this_pi / 60.0; //Paddle initialised with rate of change of 1/60 pi per frame
   
   speed = 4;
   
   if(!valid()) throw InvalidPaddle{};
}

bool Paddle::valid()
{
   return ( width >= 4 &&
      thickness >= 1 &&
      pos_max > 0 &&
      pos_min >= 0 &&
      pos_max - pos_min > 7 &&
      position.hori <= pos_max &&
      position.hori >= pos_min );
}
