#include "../src/gui.cpp"
#include <iostream>

int main( int argc, char* argv[] )
{
   std::cout << "Started\n";
   
   GUI context {500, 500};
   
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
   
   return 0;
}

