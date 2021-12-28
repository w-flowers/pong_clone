
/*******************************************************************************
* Pong Clone - Config (config.hpp) 
*
* Read in data from a configuration file. The file determines the number of
* balls, edges, who they belong to and the size of the field. It also determines
* whether the code is a simulation or a game.
*
* Author: William Flowers
*******************************************************************************/

#ifndef PONG_CONFIG

#define PONG_CONFIG

#include <iostream>

enum Gametype { sim, multiplayer };

struct Ball_Args
{
   int r {};

   double init_x {};

   double init_y {};

   double speed {};
};

struct Line_Object_Args
{
   struct position pos_1 {};

   struct position pos_2 {};

   Linetype t {edge};

   Player p {none};
};

struct Configuration
{
   Gametype gametype {sim};

   int window_width {1000};

   int window_height {800};

   std::vector< Ball_Args > balls {};

   std::vector< Line_Object_Args > lines {};

   int gametype_set_count {0};

   int dimensions_set_count {0};
};

// Exception for if read_config_file is fed bad input
class InvalidConfig {};

void run_configuration( Configuration& config, std::string filepath );

void read_config_file( Configuration& config, std::ifstream input );

void process_config_line( Configuration& config,
                          std::vector< std::string >& tokens );

void parse_gametype_line( Configuration& config,
                         std::vector< std::string >& tokens );

void parse_dimensions_line( Configuration& config,
                         std::vector< std::string >& tokens );

#endif

