/******************************************************************************
 * ballsim.cpp - a test function which runs a ball simulator program
 *
 * Author: William Flowers
 *
 * Includes the main function which creates a working program which simply tests
 * the SDL_Event loop, the Timer, Rendering and Collision detection of the basic
 * classes. Will not include all gameplay features.
 * ***************************************************************************/

#include "../../inc/gui.hpp"

#include "../../inc/field.hpp"

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

   ball_init.reserve(256);

   for(int i = 0; i < 27; i++)
   {
      BallArgs temp {10 + i % 5, 30*( i + 4 ), 300 + 2*i, 0.5 + 0.001 * i};

      ball_init.push_back( temp );
   }

   for(int i = 0; i < 27; i++)
   {
      BallArgs temp {10 - i % 5, 30*( i + 4 ), 400, 0.5 + 0.001 * i};

      ball_init.push_back( temp );
   }

   for(int i = 0; i < 27; i++)
   {
      BallArgs temp {10 - i % 5, 30*( i + 4 ), 450, 0.5 - 0.01 * i};

      ball_init.push_back( temp );
   }

   for(int i = 0; i < 27; i++)
   {
      BallArgs temp {5 + i % 10, 30*( i + 4 ), 240, 0.5};

      ball_init.push_back( temp );
   }

   for(int i = 0; i < 27; i++)
   {
      BallArgs temp {5 + i % 10, 30*( i + 4 ), 210, 0.5};

      ball_init.push_back( temp );
   }

   for(int i = 0; i < 27; i++)
   {
      BallArgs temp {5 + i % 10, 30*( i + 4 ), 480, 0.5};

      ball_init.push_back( temp );
   }

   Field test_field {list, ball_init, 1000, 800, 150, 100};
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

      //SDL_Delay(200);

      //Render
      gui.render_all( test_field );
   }

   return 0;
}

