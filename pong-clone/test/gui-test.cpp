#include "../src/gui.cpp"
#include <iostream>

int main( int argc, char* argv[] )
{
   std::cout << "Started\n";
   std::cout << "Started\n";
   
   
   SDL_Init( SDL_INIT_VIDEO );

   SDL_Window *window = nullptr;

   window = SDL_CreateWindow( "Pong Clone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                     500, 500, SDL_WINDOW_SHOWN );

   SDL_Renderer *renderer = SDL_CreateRenderer( window, -1, 0 );                  

   std::cout << "Started 4\n";
   
   std::cout << "Ended\n";
   
   //context.render();
   
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
   SDL_DestroyRenderer(renderer);

   SDL_DestroyWindow(window);

   SDL_Quit(); 
   
   GUI context {500, 500};
   
   std::cout << "Started 4\n";
   
   std::cout << "Ended\n";
   
   //context.render();
   
   quit = false;
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
   
   return 0;
}

