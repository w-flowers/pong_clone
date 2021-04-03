
/********************************************************************************
* Pong Clone - Physics (physics.cpp) 
*
* File containing the functions and classes making up the physics engine. To be
* populated in order to better seperate concerns in base classes and enable
* implementation of better algorithms.
*
* Author: William Flowers
********************************************************************************/

#include "../inc/physics.hpp"

void Engine::bounce( Ball& ball, float edge_angle )
{
      float newangle = 2 * edge_angle - ball.vel_angle();
      
      ball.set_velocity( 
            //x value
            static_cast<int>( lroundf( ball.get_speed() * cosf( newangle ) ) )

            //y value
            static_cast<int>( lroundf( ball.get_speed() * sinf( newangle ) ) ),
            );
      
      return;
}
