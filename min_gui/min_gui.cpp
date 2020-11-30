#include <SDL2/SDL.h>

#include <iostream>

int main(void)
{
   if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) std::cout << "Failed init";

   else
   {
      SDL_Window *window = SDL_CreateWindow( "Pong Clone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN );

      SDL_Renderer *renderer = SDL_CreateRenderer( window, -1, 0 );

      SDL_Event e;
      bool quit = false;
      while (!quit){
          while (SDL_PollEvent(&e)){
              if (e.type == SDL_QUIT){
                  quit = true;
             }
               if (e.type == SDL_KEYDOWN){
                  quit = true;
               }
               if (e.type == SDL_MOUSEBUTTONDOWN){
                  quit = true;
               }
          }
      }
   }
   return 0;
}

