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

void GUI::render_all( Field& field )
{
   SDL_RenderClear( renderer.get_renderer() );

   render_background();

   for( int i = 0; i < field.ball_vec_size(); i++ )
   {
      render_ball( field.get_ball( i ) );
   }

   for( int i = 0; i < field.boundary.get_lines_size(); i++ )
   {
      render_line( field.boundary.get_line( i ) );
   }
   
   SDL_RenderPresent( renderer.get_renderer() );
}

void GUI::render_line( Line_Object& line_o )
{
   SDL_SetRenderDrawColor( renderer.get_renderer(), 0, 0, 0, 0 );

   SDL_RenderDrawLine( renderer.get_renderer(), line_o.line.get_p1().x, 
         line_o.line.get_p1().y, line_o.line.get_p2().x,
         line_o.line.get_p2().y );
}

void GUI::render_ball( Ball& ball )
{
   SDL_SetRenderDrawColor( renderer.get_renderer(), 0, 0, 0, 0 );

   // Placeholder for a proper ball drawing method
   SDL_RenderDrawPoint( renderer.get_renderer(), ball.get_position().x,
         ball.get_position().y );

   SDL_RenderDrawPoint( renderer.get_renderer(), 
         ball.get_position().x + ball.get_radius(),
         ball.get_position().y );

   SDL_RenderDrawPoint( renderer.get_renderer(), 
         ball.get_position().x - ball.get_radius(),
         ball.get_position().y );

   SDL_RenderDrawPoint( renderer.get_renderer(), 
         ball.get_position().x ,
         ball.get_position().y + ball.get_radius() );

   SDL_RenderDrawPoint( renderer.get_renderer(), 
         ball.get_position().x,
         ball.get_position().y - ball.get_radius() );
}

void GUI::render_background()
{
   SDL_SetRenderDrawColor( renderer.get_renderer(), 255, 255, 255, 0 );

   SDL_RenderFillRect( renderer.get_renderer(), NULL );
}

GUI::~GUI()
{  
   renderer.~Renderer();
   
   window.~Window();
}


