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
   if( ball_textures.size() == 0 )
   {
      ball_textures.reserve( field.ball_vec_size() );

      for( int i = 0; i < field.ball_vec_size(); i++ )
      {
         // Render balls to SDL texture here
         ball_textures.push_back(
               SDL_CreateTexture( renderer.get_renderer(),
                  SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET,
                  2 * field.get_ball( i ).get_radius() + 1, 
                  2 * field.get_ball( i ).get_radius() + 1
                  )
               );

         SDL_SetTextureBlendMode( ball_textures.at(i), SDL_BLENDMODE_BLEND );

         render_ball( field.get_ball( i ), i );
      }
   }

   SDL_RenderClear( renderer.get_renderer() );

   render_background();

   for( int i = 0; i < field.ball_vec_size(); i++ )
   {
      copy_ball_textures( field.get_ball(i), i );
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

void GUI::render_ball( Ball& ball, int index )
{
   SDL_SetRenderDrawColor( renderer.get_renderer(), 255, 255, 255, 0 );

   SDL_SetRenderTarget( renderer.get_renderer(), ball_textures.at( index ) );

   SDL_RenderFillRect( renderer.get_renderer(), NULL );

   SDL_SetRenderDrawColor( renderer.get_renderer(), 0, 0, 0, 255 );

   // Placeholder for a proper ball drawing method
   /*SDL_RenderDrawPoint( renderer.get_renderer(), ball.get_position().x,
         ball.get_position().y );

   SDL_RenderDrawPoint( renderer.get_renderer(), 
         ball.get_position().x + ball.get_radius(),
         ball.get_position().y );

   SDL_RenderDrawPoint( renderer.get_renderer(), 
         ball.get_position().x - ball.get_radius(),
         ball.get_position().y );
*/
   SDL_RenderDrawLine( renderer.get_renderer(), 
         2 * ball.get_radius(), 
         ball.get_radius(), 
         0,
         ball.get_radius() );
   
   /*SDL_RenderDrawPoint( renderer.get_renderer(), 
         ball.get_position().x ,
         ball.get_position().y + ball.get_radius() );

   SDL_RenderDrawPoint( renderer.get_renderer(), 
         ball.get_position().x,
         ball.get_position().y - ball.get_radius() );
*/
   
   SDL_RenderDrawLine( renderer.get_renderer(), 
         ball.get_radius(), 
         2* ball.get_radius(), 
         ball.get_radius(),
         0 );

   int n = 0;

   int r = ball.get_radius();

   int x = r;

   int x_inc = 0;

   while( ++n < x )
   {
      x_inc = ( ( x*x + n*n - r*r - r ) > 0 );

      x -= x_inc;

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.get_radius() + x,
            ball.get_radius() + n);

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.get_radius() + x,
            ball.get_radius() - n);

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.get_radius() - x,
            ball.get_radius() + n);

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.get_radius() - x,
            ball.get_radius() - n);

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.get_radius() + n,
            ball.get_radius() + x);

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.get_radius() + n,
            ball.get_radius() - x);

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.get_radius() - n,
            ball.get_radius() + x);

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.get_radius() - n,
            ball.get_radius() - x);
   }

   SDL_SetRenderTarget( renderer.get_renderer(), NULL );
}

void GUI::copy_ball_textures( Ball& ball, int index )
{
   SDL_Rect temp { round( ball.get_position().x ) - ball.get_radius(),
      round( ball.get_position().y ) - ball.get_radius(),
      2 * ball.get_radius() + 1,
      2 * ball.get_radius() + 1
   };

   SDL_RenderCopy( renderer.get_renderer(), ball_textures.at( index ),
         NULL, &temp );
}

void GUI::render_background()
{
   SDL_SetRenderDrawColor( renderer.get_renderer(), 255, 255, 255, 0 );

   SDL_RenderFillRect( renderer.get_renderer(), NULL );
}

GUI::~GUI()
{  
   for( SDL_Texture * texts : ball_textures )
   {
      SDL_DestroyTexture(texts);
   }

   renderer.~Renderer();
   
   window.~Window();
}


