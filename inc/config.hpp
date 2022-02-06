
/*******************************************************************************
* Pong Clone - Config (config.hpp) 
*
* Read in data from a configuration file. The file determines the number of
* balls, edges, who they belong to and the size of the field. It also determines
* whether the code is a simulation or a game.
*
* The struct configuration is defined in pong_clone_base to allow it to be used
* by the field class for initialisation.
*
* Author: William Flowers
*******************************************************************************/

#ifndef PONG_CONFIG

#define PONG_CONFIG

#include <iostream>

#include <sstream>

#include <filesystem>

#include <fstream>

#include "pong_clone_base.hpp"

#include "line.hpp"

// Exception for if read_config_file is fed bad input
class InvalidConfig {};

void run_configuration( Configuration& config, std::string& filepath );

void read_config_file( Configuration& config, std::ifstream& input );

void process_config_line( Configuration& config,
                          std::vector< std::string >& tokens );

void parse_gametype_line( Configuration& config,
                         std::vector< std::string >& tokens );

void parse_dimensions_line( Configuration& config,
                         std::vector< std::string >& tokens );

void parse_line_line( Configuration& config,
                          std::vector< std::string >& tokens );

void parse_ball_line( Configuration& config,
                          std::vector< std::string >& tokens );

#endif

