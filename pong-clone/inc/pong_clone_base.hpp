
/******************************************************************************
 * pong_clone_base.hpp
 *
 * A header which defines constants and expressions that will be used accross
 * the entire codebase and which will not be expected to change.
 *
 * Author: William Flowers
 * ***************************************************************************/

#include <SDL2/SDL.h>

#include <cmath>

const float this_pi = 3.141593; //local definition of pi, may change in future

const int fps = 30;

struct position 
{
   int x;
   int y;
};
