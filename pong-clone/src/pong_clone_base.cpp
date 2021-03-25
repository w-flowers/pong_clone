
/******************************************************************************
 * pong_clone_base.hpp
 *
 * A header which defines constants, functions and expressions that will be used
 * across the entire codebase and which will not be expected to change.
 *
 * Author: William Flowers
 * ***************************************************************************/

#include "../inc/pong_clone_base.hpp"

float square_float( float a )
{
   return a * a;
}

bool approx_equal_anglesf( float a, float b )
{
   return fabs( a - b ) < 0.00001;
}

