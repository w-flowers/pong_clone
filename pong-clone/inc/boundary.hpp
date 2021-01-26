
/********************************************************************************
* Pong Clone - boundary (boundary.hpp) 
*
* DESCRIPTION
*
* Author: William Flowers
********************************************************************************/

#ifndef BOUNDARY_HPP

#define BOUNDARY_HPP

#include "pong_clone_base.hpp"

#include "line.hpp"

class Boundary
{
public:
   Boundary();

private:
   std::vector<Line> game_bounds;
};

#endif

