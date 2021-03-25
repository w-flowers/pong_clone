/********************************************************************************
* Pong Clone - boundary (boundary.cpp) 
*
* A class to manage the boundary of the game. Stores a vector of the game and
* provides initialisation based on a list of points. Will always return a closed
* polygon.
*
* Author: William Flowers
********************************************************************************/

#include "../inc/boundary.hpp"

Boundary::Boundary( std::vector<Line_start> init_list, int ball_radius )
{
   for( auto i = 0; i < init_list.size() - 1; i++ )
   {
      create_segment( init_list[i].pos, init_list[i + 1].pos, 
            init_list[i].type, ball_radius );
   }
   
  create_segment( init_list.back().pos, init_list.front().pos, 
        init_list.back().type, ball_radius );
}

void Boundary::create_segment( struct position pos_1, struct position pos_2,
      Linetype seg_type, int ball_radius )
{
   if( seg_type == edge )
   {
      game_bounds.emplace_back( Edge( pos_1, pos_2, ball_radius ) ); 
   }
   else if( seg_type == goal )
   {
      //MUST BE CHANGED TO GOAL LATER
      game_bounds.emplace_back( Edge( pos_1, pos_2, ball_radius ) ); 
   }
}
