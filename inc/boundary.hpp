
/********************************************************************************
* Pong Clone - boundary (boundary.hpp) 
*
* A class to manage the boundary of the game. Stores a vector of the game and
* provides initialisation based on a list of points. Will always return a closed
* polygon.
*
* Author: William Flowers
********************************************************************************/

#ifndef BOUNDARY_HPP

#define BOUNDARY_HPP

#include "pong_clone_base.hpp"

#include "line.hpp"

//Struct used to initialise boundary
struct Line_start
{
   struct position pos;

   Linetype type;

   Player player;
};



class Boundary
{
public:
   //Initialise boundary using a list of points and edge types.
   //Boundary() will join the points into a polygon.
   //It is the caller's responsibility to ensure that the points passed in
   //are reasonable.
   Boundary( const std::vector<Line_start>& init_list );

   //return edge at vector index
   Line_Object& get_line( int index );

   //return size of vector of edges
   int get_lines_size();

   class InvalidLinetype{};
private:
   std::vector<Line_Object> game_bounds;

   // DEPRECATED
   //helper method to insert line segments into game bounds vector
//   void create_segment( struct position pos_1, struct position pos_2,
//         Linetype seg_type, Player p );
};

#endif

