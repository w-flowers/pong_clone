
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

void run_configuration( Configuration& config, std::string& filepath )
{
   // Open file given by filepath

   std::filesystem::path input_path {filepath};

   std::ifstream input {input_path};
   
   // Read Configuration file - store output in Configuration struct
   
   read_config_file( config, input );
}

void read_config_file( Configuration& config, std::ifstream& input )
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

      if( tokens.size() > 0 )
      {
         process_config_line( config, tokens );
      }

      tokens.clear();
   }
}

void process_config_line( Configuration& config,
                          std::vector< std::string >& tokens )
{
   if( tokens.at(0) == "gametype" )
   {
      parse_gametype_line( config, tokens );
   }

   else if( tokens.at(0) == "dimensions" )
   {
      parse_dimensions_line( config, tokens );
   }

   else if( tokens.at(0) == "line" )
   {
      parse_line_line( config, tokens );
   }

   else if( tokens.at(0) == "ball" )
   {
      parse_ball_line( config, tokens );
   }

   else
   {
      std::cerr << "Invalid initial token.\n";

      throw InvalidConfig{};
   }
}

void parse_gametype_line( Configuration& config,
                          std::vector< std::string >& tokens )
{
   if( tokens.size() != 2 || ++( config.gametype_set_count ) > 1 )
   {
      std::cerr << "Invalid gametype line.\ngametype_set_count: " <<
         config.gametype_set_count << "\ntoken count: " <<
         tokens.size() << "\n";

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
      std::cerr << "Invalid gametype.\n";

      throw InvalidConfig{};
   }
}

void parse_dimensions_line( Configuration& config,
                          std::vector< std::string >& tokens )
{
   if( tokens.size() != 3 || ++( config.dimensions_set_count ) > 1 )
   {
      std::cerr << "Invalid dimensions line.\ndimensions_set_count: " <<
         config.dimensions_set_count << "\ntoken count: " <<
         tokens.size() << "\n";

      throw InvalidConfig{};
   }

   config.window_width = std::stoi( tokens.at(1) );

   config.window_height = std::stoi( tokens.at(2) );

   if( config.window_width <= 0 || config.window_height <= 0 )
   {
      std::cerr << "Invalid dimensions.\n";

      throw InvalidConfig{};
   }
}

void parse_line_line( Configuration& config,
                          std::vector< std::string >& tokens )
{
   if( config.gametype_set_count != 1
    || config.dimensions_set_count != 1
    || ( config.gametype == sim && tokens.size() != 6 )
    || ( config.gametype == multiplayer && tokens.size() != 7 ) )
   {
      std::cerr << "Invalid line line.\ngametype_set_count: " <<
         config.gametype_set_count << "\ndimensions_set_count: " <<
         config.dimensions_set_count << "\ntoken count: " <<
         tokens.size() << "\n";

      throw InvalidConfig{};
   }

   config.lines.emplace_back();

   Line_Object_Args& new_line = config.lines.back();

   if( tokens.at(1) == "edge" )
   {
      new_line.t = edge;
   }

   else if( tokens.at(1) == "goal" )
   {
      new_line.t = goal;
   }

   else if( tokens.at(1) == "paddle" )
   {
      new_line.t = paddle;
   }
   
   else
   {
      std::cerr << "Invalid linetype.\n";

      throw InvalidConfig{};
   }

   new_line.pos_1.x = std::stoi( tokens.at(2) );

   new_line.pos_1.y = std::stoi( tokens.at(3) );

   new_line.pos_2.x = std::stoi( tokens.at(4) );

   new_line.pos_2.y = std::stoi( tokens.at(5) );

   // Checks for valid player values by linetype, and throws exception
   // if values are not consistent with linetype
   if( config.gametype == multiplayer )
   {
      if( tokens.at(6) == "1" && new_line.t != edge )
      {
         new_line.p = pl_1;
      }

      else if( tokens.at(6) == "2" && new_line.t != edge )
      {
         new_line.p = pl_2;
      }

      else if( tokens.at(6) == "0" && new_line.t == edge )
      {
         // does nothing - included for clarity
         new_line.p = none;
      }

      else
      {
         std::cerr << "Invalid player value.\n";

         throw InvalidConfig{};
      }
   }

   // Check all line endpoints are contained in game window
   if( new_line.pos_1.x <= 0 || new_line.pos_1.x >= config.window_width
    || new_line.pos_2.x <= 0 || new_line.pos_2.x >= config.window_width 
    || new_line.pos_1.y <= 0 || new_line.pos_1.y >= config.window_height
    || new_line.pos_2.y <= 0 || new_line.pos_2.y >= config.window_height )
   {
      std::cerr << "Line out of bounds.\n";

      throw InvalidConfig{};
   }
}

void parse_ball_line( Configuration& config,
                          std::vector< std::string >& tokens )
{
   if( tokens.size() != 5 || config.dimensions_set_count != 1 )
   {
      std::cerr << "Invalid ball line.\ndimensions_set_count: " <<
         config.dimensions_set_count << "\ntoken count: " <<
         tokens.size() << "\n";

      throw InvalidConfig{};
   }

   config.balls.emplace_back();

   Ball_Args& new_ball = config.balls.back();

   new_ball.r = std::stoi( tokens.at(1) );

   new_ball.init_x = std::stod( tokens.at(2) );

   new_ball.init_y = std::stod( tokens.at(3) );

   new_ball.speed = std::stod( tokens.at(4) );

   // Check new ball is in bounds
   if( new_ball.init_x - static_cast<double>( new_ball.r ) <= 0
    || new_ball.init_x + static_cast<double>( new_ball.r )
         >= static_cast<double>( config.window_width )
    || new_ball.init_y - static_cast<double>( new_ball.r ) <= 0
    || new_ball.init_y + static_cast<double>( new_ball.r )
         >= static_cast<double>( config.window_height ) )
   {
      std::cerr << "Ball out of bounds.\n";

      throw InvalidConfig{};
   }
}
