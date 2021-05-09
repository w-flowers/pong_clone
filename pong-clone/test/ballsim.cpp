/******************************************************************************
 * ballsim.cpp - a test function which runs a ball simulator program
 *
 * Author: William Flowers
 *
 * Includes the main function which creates a working program which simply tests
 * the SDL_Event loop, the Timer, Rendering and Collision detection of the basic
 * classes. Will not include all gameplay features.
 * ***************************************************************************/

#include "../inc/gui.hpp"

#include "../inc/field.hpp"

int main( int argc, char* argv[] )
{
   GUI gui {1000, 800};

   std::vector<Line_start> list {};

   list.reserve(20);

   for(int i = 1; i < 11; i++)
   {
      Line_start temp {{90*i, 100*( i%2 ) + i * 10}, edge, none};

      list.push_back(temp);
   }

   for(int i = 10; i > 0; i--)
   {
      Line_start temp {{91*i, 600 - 100 * ( i%2 ) }, edge, none};

      list.push_back(temp);
   }

   std::vector<BallArgs> ball_init;

   ball_init.reserve(6);

   for(int i = 0; i < 14; i++)
   {
      BallArgs temp {20 + i, 60*( i + 2 ), 300 + 2*i, 0.6};

      ball_init.push_back( temp );
   }

   for(int i = 0; i < 14; i++)
   {
      BallArgs temp {20 - i, 60*( i + 2 ), 400, 0.6};

      ball_init.push_back( temp );
   }

   for(int i = 0; i < 14; i++)
   {
      BallArgs temp {15 + i, 60*( i + 2 ), 240, 0.6};

      ball_init.push_back( temp );
   }

   Field test_field {list, ball_init, 1000, 800, 8, 5};
   SDL_Event e;

   bool quit = false;

   while ( !quit )
   {
       while ( SDL_PollEvent( &e ) )
       {
           if ( e.type == SDL_QUIT )
           {
               quit = true;
           }
       }
       //Move game objects
       test_field.advance_field();

       test_field.advance_field();

       test_field.advance_field();

       //Render
       gui.render_all( test_field );
   }

   return 0;
}

