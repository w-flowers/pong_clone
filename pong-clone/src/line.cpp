
/******************************************************************************
 * Pong-clone - Line (line.cpp) 
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
 *****************************************************************************/

#include "../inc/line.hpp"


Line::Line( int x1_, int y1_, int x2_, int y2_ ):
   x1{x1_}, y1{y1_}, x2{x2_}, y2{y2_}
{}

void Line::set_colour(SDL_Color colour)
{
   line_colour.r = colour.r;

   line_colour.g = colour.g;

   line_colour.b = colour.b;

   line_colour.a = colour.a;
}

Collidable::Collidable( int x1_, int y1_, int x2_, int y2_, int br //ball radius )
{
   Line::Line(x1_, y1_, x2_, y2_);

   line_angle = atan2f( ( (float) (y2 - y1) ), ( (float) (x2 - x1) ) );

   ocb_tl.x = ( x1 > x2 ) ? ( x2 - br ) : ( x1 - br ) ;

   ocb_tl.y = ( y1 > y2 ) ? ( y2 - br ) : ( y1 - br ) ;

   ocb_br.x = ( x1 > x2 ) ? ( x1 + br ) : ( x2 + br ) ;

   ocb_br.y = ( y1 > y2 ) ? ( y1 + br ) : ( y2 + br ) ;

   //find appropriate bounds for inner container box
   
   icb_x_offset = 0;

   icb_y_offset = 0;

   icb_tl.x = ( x1 > x2 ) ? ( x2 - icb_x_offset ) : ( x1 - icb_x_offset ) ;

   icb_tl.y = ( y1 > y2 ) ? ( y2 - icb_y_offset ) : ( y1 - icb_y_offset ) ;

   icb_br.x = ( x1 > x2 ) ? ( x1 + icb_x_offset ) : ( x2 + icb_x_offset ) ;

   icb_br.y = ( y1 > y2 ) ? ( y1 + icb_y_offset ) : ( y2 + icb_y_offset ) ;
}

float Collidable::get_line_angle()
{
   return line_angle;
}

