
/******************************************************************************
 * pong_clone_base.hpp
 *
 * A header which defines constants, functions and expressions that will be used
 * across the entire codebase and which will not be expected to change.
 *
 * Author: William Flowers
 * ***************************************************************************/

#ifndef PONG_CLONE_BASE

#define PONG_CLONE_BASE

#include <SDL2/SDL.h>

#include <iostream>

#include <vector>

#include <cmath>

#include <unordered_map>

#include <set>

#include <unordered_set>

const float this_pi = 3.141593; //local definition of pi, may change in future

const int fps = 30;

struct position 
{
   int x;
   int y;
};

bool operator<( const position&, const position& );

struct positionf 
{
   float x;
   float y;
};

struct positiond
{
   double x;
   double y;
};

//Ball data for drawing
struct ball_pos_data
{
   position_d centre;

   double radius;
}

//Line data for drawing
struct line_pos_data
{
   position p1;

   position p2;

   Linetype t;
}

// Structure for transferring data from game server to GUI client
struct field_position_data
{
   std::vector< ball_pos_data > ball_positions {};

   std::vector< line_pos_data > line_positions {};
};

//TO DO: Structure for transferring commands from GUI to game server

enum Player {pl_1, pl_2, none};

// Convenience function, don't want overhead of using exp
float square_float( float a );

int square_int( int a );

double square_d( double a );

// Function for testing purposes. Should not be used for actual equality tests
bool approx_equal_anglesf( float a, float b );

// Function for testing purposes. Should not be used for actual equality tests
bool approx_equal_anglesd( double a, double b );

#endif
