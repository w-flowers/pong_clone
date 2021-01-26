
/******************************************************************************
 * pong_clone_base.hpp
 *
 * A header which defines constants and expressions that will be used accross
 * the entire codebase and which will not be expected to change.
 *
 * Author: William Flowers
 * ***************************************************************************/

#ifndef PONG_CLONE_BASE

#define PONG_CLONE_BASE

#include <SDL2/SDL.h>

#include <vector>

#include <cmath>

const float this_pi = 3.141593; //local definition of pi, may change in future

const int fps = 30;

struct position 
{
   int x;
   int y;
};

struct positionf 
{
   float x;
   float y;
};

#endif
