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

void GUI::render_all( field_position_data& field )
{
   if( ball_textures.size() == 0 )
   {
      ball_textures.reserve( field.ball_positions.size() );

      for( int i = 0; i < field.ball_positions.size(); i++ )
      {
         // Render balls to SDL texture here
         ball_textures.push_back(
               SDL_CreateTexture( renderer.get_renderer(),
                  SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET,
                  2 * field.ball_positions[ i ].radius + 1, 
                  2 * field.ball_positions[ i ].radius + 1
                  )
               );

         SDL_SetTextureBlendMode( ball_textures.at(i), SDL_BLENDMODE_BLEND );

         render_ball( field.ball_positions[i], i );
      }
   }

   SDL_RenderClear( renderer.get_renderer() );

   render_background();

   for( int i = 0; i < field.ball_positions.size(); i++ )
   {
      copy_ball_textures( field.ball_positions[i], i );
   }

   for( int i = 0; i < field.line_positions.size(); i++ )
   {
      render_line( field.line_positions[i] );
   }
   
   SDL_RenderPresent( renderer.get_renderer() );
}

void GUI::render_line( line_pos_data& line_o )
{
   SDL_SetRenderDrawColor( renderer.get_renderer(), 0, 0, 0, 0 );

   SDL_RenderDrawLine( renderer.get_renderer(), line_o.p1.x, 
         line_o.p1.y, line_o.p2.x,
         line_o.p2.y );
}

void GUI::render_ball( ball_pos_data& ball, int index )
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
         2 * ball.radius, 
         ball.radius, 
         0,
         ball.radius );
   
   /*SDL_RenderDrawPoint( renderer.get_renderer(), 
         ball.get_position().x ,
         ball.get_position().y + ball.get_radius() );

   SDL_RenderDrawPoint( renderer.get_renderer(), 
         ball.get_position().x,
         ball.get_position().y - ball.get_radius() );
*/
   
   SDL_RenderDrawLine( renderer.get_renderer(), 
         ball.radius, 
         2* ball.radius, 
         ball.radius,
         0 );

   int n = 0;

   int r = ball.radius;

   int x = r;

   int x_inc = 0;

   while( ++n < x )
   {
      x_inc = ( ( x*x + n*n - r*r - r ) > 0 );

      x -= x_inc;

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.radius + x,
            ball.radius + n);

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.radius + x,
            ball.radius - n);

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.radius - x,
            ball.radius + n);

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.radius - x,
            ball.radius - n);

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.radius + n,
            ball.radius + x);

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.radius + n,
            ball.radius - x);

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.radius - n,
            ball.radius + x);

      SDL_RenderDrawPoint( renderer.get_renderer(), 
            ball.radius - n,
            ball.radius - x);
   }

   SDL_SetRenderTarget( renderer.get_renderer(), NULL );
}

void GUI::copy_ball_textures( ball_pos_data& ball, int index )
{
   SDL_Rect temp { ball.rounded_x - ball.radius,
      ball.rounded_y - ball.radius,
      2 * ball.radius + 1,
      2 * ball.radius + 1
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


