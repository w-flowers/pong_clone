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

Boundary::Boundary( std::vector<Line_start> init_list )
{
   for( auto i = 0; i < init_list.size() - 1; i++ )
   {
      if( init_list[i].type == paddle )
      {
         throw InvalidLinetype{};
      }

      game_bounds.emplace_back( Line_Object( init_list[i].pos, init_list[i + 1].pos, 
            init_list[i].type, init_list[i].player ) );
   }
   
   if( init_list.back().type == paddle )
   {
      throw InvalidLinetype{};
   }

   game_bounds.emplace_back( Line_Object( init_list.back().pos, init_list.front().pos, 
        init_list.back().type, init_list.back().player ) );
}

Line_Object& Boundary::get_line( int index )
{
   return game_bounds.at( index );
}

int Boundary::get_lines_size()
{
   return game_bounds.size();
}

/* DEPRECATED

void Boundary::create_segment( struct position pos_1, struct position pos_2,
      Linetype seg_type, Player p )
{
   if( seg_type == edge )
   {
      game_bounds.emplace_back( Line_Object( pos_1, pos_2 ) ); 
   }
   else if( seg_type == goal )
   {
      //MUST BE CHANGED TO GOAL LATER
      game_bounds.emplace_back( Line_( pos_1, pos_2 ) ); 
   }
}*/
