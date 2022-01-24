/******************************************************************************
 * Eventual location where the main function will be defined
 *
 * Likely to simply be a wrapper to a "run" function in the GUI class
 * ***************************************************************************/

#include "../../inc/game.hpp"

int main( int argc, char *argv[] )
{
   if( argc == 1 )
   {
      std::cout << "Please select a config file to load.\n";

      return 1;
   }

   else if( argc == 2 )
   {
      std::string filename {argv[1]};

      Game::run( filename );
   }

   else
   {
      std::cout <<
         "Too many arguments supplied - please enter a single filename\n";

      return 1;
   }

   return 0;
}
