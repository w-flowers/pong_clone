/********************************************************************************
* Pong Clone - boundary (boundary.cpp) 
*
* A class to manage the boundary of the game. Stores a vector of the game and
* provides initialisation based on a list of points. Will always return a closed
* polygon.
*
* Author: William Flowers
********************************************************************************/


Boundary::Boundary( std::vector<Line_start> init_list, int ball_radius )
{
   for( int i = 0; i < init_list.size() - 1, i++ )
   {
      game_bounds.emplace_back( create_segment( init_list[i].pos, init_list[i + 1].pos, 
            init_list[i].type, ball_radius ) );
   }
   
  game_bounds.emplace_back( create_segment( init_list.back().pos, init_list.front().pos, 
        init_list.back.type, ball_radius ) );
}

Boundary::create_segment( pos_1, pos_2, seg_type, ball_radius )
{
   if( seg_type == edge )
   {
      Edge( pos_1, pos_2, ball_radius ); 
   }
   else if( seg_type == goal )
   {
      //MUST BE CHANGED TO GOAL LATER
      Edge( pos_1, pos_2, ball_radius ); 
   }
}
