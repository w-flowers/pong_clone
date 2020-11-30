#include <cmath>

/********************************************************************************

Class describing the game ball

All units measured in an integer number of pixels

********************************************************************************/
//Default ball values
#define DEFX 0
#define DEFY 0
#define DEFSPD 0
#define DEFDX 0
#define DEFDY 0

const float this_pi = 3.141593;

class Ball
{
public:
   
   Ball(int radius);
   
   void bounce(float edge_angle)
   {
      float newangle = 2 * edge_angle - vel_angle();
      
      velocity.dy = (int) lroundf(velocity.speed * sinf( newangle ));
      
      velocity.dx = (int) lroundf(velocity.speed * cosf( newangle ));
      
      return;
   };

   void move()
   {
      position.hori += velocity.dx;

      position.vert += velocity.dy;
   };
   
private:
   
   int radius;
   
   struct velocity
   {
      int dx;
      
      int dy;
      
      float speed;
   } velocity;
   
   struct position
   {
      int hori;
      
      int vert;
   } position;
   
   class InvalidBall {};
   
   //calculate angle of balls movement from horizontal - range from +pi to -pi
   float vel_angle()
   {
      return atan2f(((float) dy), ((float) dx));
   };
};

Ball::Ball(int r)
{
   if( r <= 0 ) throw InvalidBall{};
   radius = r;

   velocity.dx = DEFDX;

   velocity.dy = DEFDY;

   velocity.speed = DEFSPD;

   position.hori = DEFX;

   position.vert = DEFY;

   return;
}

