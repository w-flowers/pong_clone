#include "../inc/gui.hpp"

Window::Window(int width, int height)
{
   if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) throw FailedInit{};

   window = SDL_CreateWindow( "Pong Clone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                     width, height, SDL_WINDOW_SHOWN );
                     
   if( window == nullptr )
   {
      throw FailedInit{};
   }
   
}

Window::~Window()
{
   SDL_DestroyWindow( window );

   SDL_Quit();
}

SDL_Window *Window::get_window()
{
   return window;
}

Renderer::Renderer(Window& newwindow)
{  
   if( newwindow.get_window() == nullptr ) throw FailedInit{};
   
   renderer = SDL_CreateRenderer( newwindow.get_window(), -1, SDL_RENDERER_PRESENTVSYNC );
   
   if( renderer == nullptr )
   {
      throw FailedInit{};
   }
   
}

Renderer::~Renderer()
{
   SDL_DestroyRenderer( renderer );
}

SDL_Renderer *Renderer::get_renderer()
{
   return renderer;
}

GUI::GUI(int width, int height):
   window{width, height}, renderer{window}
{ 
}

GUI::~GUI()
{  
   renderer.~Renderer();
   
   window.~Window();
}

void GUI::run()
{
   //insert body here

   game_loop();

   return;
}

void GUI::game_loop()
{
   //insert body here
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
   }
   
   return;
}

