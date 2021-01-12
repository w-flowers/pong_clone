
/********************************************************************************
* Pong Clone - game_object (game_object.hpp) 
*
* A class to provide an interface to all renderable game objects. In this class, each class
* is given access to a render method.
*
* Author: William Flowers
********************************************************************************/

#include "pong_clone_base.hpp"

class Game_object
{
public:
   virtual render(SDL_Renderer *) = 0;

   virtual ~Game_object() {};
}

