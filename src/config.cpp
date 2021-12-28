
/*******************************************************************************
* Pong Clone - Config (config.cpp) 
*
* Read in data from a configuration file. The file determines the number of
* balls, edges, who they belong to and the size of the field. It also determines
* whether the code is a simulation or a game.
*
* Author: William Flowers
*******************************************************************************/

#include "../inc/config.hpp"

void run_configuration( Configuration& config, std::string filepath )
{
   // Open file given by filepath
   
   // Read Configuration file - store output in Configuration struct
}

void read_config_file( Configuration& config, std:ifstream input )
{
   std::string line_buffer;

   std::vector< std::string > tokens {};

   while( std::getline( input, line_buffer ) )
   {
      std::istringstream line_stream( line_buffer );

      std::string input_token;

      while( line_stream >> input_token )
      {
         tokens.push_back( input_token );
      }

      process_config_line( config, tokens );
   }
}

void process_config_line( Configuration& config,
                          std::vector< std::string >& tokens )
{
   if( tokens.at(0) == "gametype" )
   {
      parse_gametype_line( config, tokens );
   }

   if( tokens.at(0) == "dimensions" )
   {
      parse_dimensions_line( config, tokens );
   }
}

void parse_gametype_line( Configuration& config,
                          std::vector< std::string >& tokens )
{
   if( tokens.length() != 2 || ++( config.gametype_set_count ) > 1 )
   {
      throw InvalidConfig{};
   }

   else if( tokens.at(1) == "sim" )
   {
      config.gametype = sim;
   }

   else if( tokens.at(1) == "multiplayer" )
   {
      config.gametype = multiplayer;
   }

   else
   {
      throw InvalidConfig{};
   }
}

void parse_dimensions_line( Configuration& config,
                          std::vector< std::string >& tokens )
{
   if( tokens.length() != 3 || ++( config.dimensions_set_count ) > 1 )
   {
      throw InvalidConfig{};
   }

   config.window_width = std::stoi( tokens.at(1) );

   config.window_height = std::stoi( tokens.at(2) );

   if( config.window_width <= 0 || config.window_height <= 0 )
   {
      throw InvalidConfig{};
   }
}
