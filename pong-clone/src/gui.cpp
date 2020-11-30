#include <SDL2/SDL.h>

#include <iostream>

const int fps = 30;

class Window
{
public:
   Window(int width, int height);
   
   Window(){};
   
   ~Window();
   
   class FailedInit{};
   
   SDL_Window *get_window()
   {
      return window;
   };
   
private:
   SDL_Window *window {nullptr};
   
};

Window::Window(int width, int height)
{
   window = SDL_CreateWindow( "Pong Clone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                     width, height, SDL_WINDOW_SHOWN );
                     
   std::cout << window << "\n";
   
   if( window == nullptr )
   {
      throw FailedInit{};
   }
   
   std::cout << "Called window\n";
}

Window::~Window()
{
   SDL_DestroyWindow( window );
}

class Renderer
{
public:
   Renderer(Window &newwindow);
   
   Renderer(){};
   
   ~Renderer();
   
   class FailedInit{};
   
   SDL_Renderer *get_renderer()
   {
      return renderer;
   };
   
private:
   SDL_Renderer *renderer {nullptr};
};

Renderer::Renderer(Window &newwindow)
{  
   if( newwindow.get_window() == nullptr ) throw FailedInit{};
   
   std::cout << "Called Rend..." << newwindow.get_window() << "\n" ;
   
   renderer = SDL_CreateRenderer( newwindow.get_window(), -1, 0 );
   
   if( renderer == nullptr )
   {
      throw FailedInit{};
   }
   
   std::cout << "Finished Rend...\n";
}

Renderer::~Renderer()
{
   SDL_DestroyRenderer( renderer );
}

class GUI 
{
public:
   GUI(int width, int height);
   
   ~GUI();
   
   class FailedInit{};
   
   void render(){};
   
private:
   Window window;
   
   Renderer renderer;
};

GUI::GUI(int width, int height)
//window{width, height}, renderer{window}
{ 
   if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) throw FailedInit{};
   
   std::cout << "Called\n";
   
   window = Window {width, height};
   
   renderer = Renderer {window};
}

GUI::~GUI()
{  
   renderer.~Renderer();
   
   window.~Window();
   
   SDL_Quit();
}


