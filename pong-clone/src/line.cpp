
/******************************************************************************
 * Pong-clone - Line (line.cpp) 
 *
 * All units an integer number of pixels. Line angle calculated according to 
 * a number plane where the positive direction is right and down, negative left
 * and up. All lines defined herein may be rendered by the program.
 *
 * Author: William Flowers
 *****************************************************************************/

#include "../inc/line.hpp"


Line::Line( struct position p1_ , struct position p2_ ):
   p1{p1_}, p2{p2_}
{
   line_angle = atan2f( 
         ( (float) ( get_p2().y - get_p1().y ) ), 
         ( (float) ( get_p2().x - get_p1().x ) ) 
         );
}

struct position Line::get_p1() const
{
   return p1;
}

struct position Line::get_p2() const
{
   return p2;
}

void set_p1( int x, int y )
{
   p1.x = x;

   p1.y = y;
}

void set_p2( int x, int y )
{
   p2.x = x;

   p2.y = y;
}

float Line::get_line_angle()
{
   return line_angle;
}

Line::~Line()
{}

Line_Object::Line_Object( struct position pos_1, struct position pos_2,
      Linetype t, Player p )
   : Line{ pos_1, pos_2 }, type{ t }
{
   if( type == edge )
   {
      if( p != none)
      {
         throw InvalidPlayerValue{};
      }
      else
      {
         player = none;
      }
   }

   else
   {
      if( p == none )
      {
         throw InvalidPlayerValue{};
      }
      else
      {
         player = p;
      }
   }
}

/* DEPRECATED - Functions moved to physics.cpp

Collidable::Collidable( struct position p1_ , struct position p2_ , int br ball radius )
   : Line( p1_, p2_ )
{
   line_angle = atan2f( ( (float) ( get_p2().y - get_p1().y ) ), ( (float) ( get_p2().x - get_p1().x ) ) );

   set_collision_boxes( br );
}

float Collidable::get_line_angle()
{
   return line_angle;
}

void Collidable::set_collision_boxes( int br )
{
   int x1 = get_p1().x;

   int x2 = get_p2().x;

   int y1 = get_p1().y;

   int y2 = get_p2().y;
   //set outer collision box

   ocb_tl.x = ( x1 > x2 ) ? ( x2 - br ) : ( x1 - br ) ;

   ocb_tl.y = ( y1 > y2 ) ? ( y2 - br ) : ( y1 - br ) ;

   ocb_br.x = ( x1 > x2 ) ? ( x1 + br ) : ( x2 + br ) ;

   ocb_br.y = ( y1 > y2 ) ? ( y1 + br ) : ( y2 + br ) ;

   //find appropriate bounds for inner container box
   
   float icb_x_offset = br * std::cos( std::abs( this_pi/2.0f - line_angle ) ); //radius * cos (|90 - alpha|)

   float icb_y_offset = br * std::sin( std::abs( this_pi/2.0f - line_angle ) ); //radius * sin (|90 - alpha|)

   icb_tl.x = ( x1 > x2 ) ? ( x2 - icb_x_offset ) : ( x1 - icb_x_offset ) ;

   icb_tl.y = ( y1 > y2 ) ? ( y2 - icb_y_offset ) : ( y1 - icb_y_offset ) ;

   icb_br.x = ( x1 > x2 ) ? ( x1 + icb_x_offset ) : ( x2 + icb_x_offset ) ;

   icb_br.y = ( y1 > y2 ) ? ( y1 + icb_y_offset ) : ( y2 + icb_y_offset ) ;
  
   return;
}

bool Collidable::in_outer_collision_box( const Ball& ball )
{
  struct position curr_pos = ball.get_position();

  return curr_pos.x >= ocb_tl.x && curr_pos.y >= ocb_tl.y && 
     curr_pos.x <= ocb_br.x && curr_pos.y <= ocb_br.y;
}

bool Collidable::is_colliding( const Ball& ball )
{
   struct position curr_pos = ball.get_position();

   int x1 = get_p1().x;

   int x2 = get_p2().x;

   int y1 = get_p1().y;

   int y2 = get_p2().y;

   if( curr_pos.x >= icb_tl.x && curr_pos.y >= icb_tl.y && 
         curr_pos.x <= icb_br.x && curr_pos.y <= icb_br.y)
   {
      //calculate distance of ball centre from line
      float ax_by_c = ( x2 - x1 ) * ( curr_pos.y - y1 ) -
         ( y2 - y1 ) * ( curr_pos.x - x1 ) ;

      float asqrd = ( x2 - x1 ) * ( x2 - x1 );

      float bsqrd = ( y2 - y1 ) * ( y2 - y1 );

      return ( ax_by_c * ax_by_c / ( asqrd + bsqrd ) <=
            ball.get_radius() * ball.get_radius() );
   }

   else
   {
      return //boolean of whether distance from ends^2 is less than ball_radius^2
         ( ( curr_pos.x - x1 ) * ( curr_pos.x - x1 ) +
           ( curr_pos.y - y1 ) * ( curr_pos.y - y1 ) <=
           ball.get_radius() * ball.get_radius() ) ||
         ( ( curr_pos.x - x2 ) * ( curr_pos.x - x2 ) +
           ( curr_pos.y - y2 ) * ( curr_pos.y - y2 ) <=
           ball.get_radius() * ball.get_radius() ) ;
   }

}

Collidable::~Collidable()
{}

Edge::Edge( struct position p1_, struct position p2_, int br )
   : Collidable( p1_, p2_, br )
{}

void Edge::collide( Ball& ball )
{
   ball.bounce( get_line_angle() );
}

Edge::~Edge()
{}
*/
