/******************************************************************************
 * gui.hpp - define core GUI functions and constructs
 *
 * Author: William Flowers
 *
 * A collection of abstractions based on SDL. Most classes here are non-copyable.
 * ***************************************************************************/

#ifndef PONG_GUI_H

#define PONG_GUI_H

#include "pong_clone_base.hpp"

#include "ball.hpp"

#include "field.hpp"

#include "line.hpp"

#include "boundary.hpp"

class Window
{
public:
   Window(int width, int height);
   
   Window(){};

   ~Window();
   
   class FailedInit{};
   
   SDL_Window *get_window();

   //Non-copyable
   Window( const Window & ) =delete;

   Window & operator=( const Window & ) =delete;
  
private:
   SDL_Window *window {nullptr};
};

class Renderer
{
public:
   Renderer(Window& newwindow);
   
   Renderer(){};
   

   ~Renderer();
   
   class FailedInit{};
   
   SDL_Renderer *get_renderer();
   
   //Non-copyable
   Renderer( const Renderer & ) =delete;

   Renderer & operator=( const Renderer & ) =delete;
  
private:
   SDL_Renderer *renderer {nullptr};
};

class GUI 
{
public:
   GUI(int width, int height);
   
   ~GUI();
   
   class FailedInit{};
   
   //Method which renders all game objects
   void render_all( Field& field );

   //Non-copyable
   GUI( const GUI & ) =delete;
   GUI & operator=( const GUI & ) =delete;
  
private:
   Window window;
   
   Renderer renderer;

   // Method which renders edges, goals and paddles
   void render_line( Line_Object& line_o );

   // Method which renders a ball
   void render_ball( Ball& ball, int index );

   // Method which takes ball textures and copies them to the balls current
   // rectangle
   void copy_ball_textures( Ball& ball, int index );

   // Render Background
   void render_background();

   // Vector of Circle textures, accessed by index of ball
   std::vector< SDL_Texture * > ball_textures {};
};

#endif
