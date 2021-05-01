
/******************************************************************************
 * pong_clone_base.hpp
 *
 * A header which defines constants, functions and expressions that will be used
 * across the entire codebase and which will not be expected to change.
 *
 * Author: William Flowers
 * ***************************************************************************/

#include "../inc/pong_clone_base.hpp"

bool operator<( const position& p1, const position& p2 )
{
   if( p1.x < p2.x ) return true;

   else if ( p1.x > p2.x ) return false;

   else
   {
      return ( p1.y < p2.y );
   }
}

float square_float( float a )
{
   return a * a;
}

double square_d( double a )
{
   return a * a;
}

int square_int( int a )
{
   return a * a;
}

bool approx_equal_anglesd( double a, double b )
{
   return abs( a - b ) < 0.000001;
}

