/******************************************************************************
 * gui.hpp - define core GUI functions and constructs
 *
 * Author: William Flowers
 *
 * A collection of abstractions based on SDL. Most classes here are non-copyable.
 *
 * Also location of the main "run" method to be invoked.
 * ***************************************************************************/

#ifndef PONG_GUI_H

#define PONG_GUI_H

#include "pong_clone_base.hpp"

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
   
   //A containing method for all the game code, to be run after setup
   void run();

   //The method which runs the game loop - called from within run
   void game_loop();

   //Non-copyable
   GUI( const GUI & ) =delete;
   GUI & operator=( const GUI & ) =delete;
  
private:
   Window window;
   
   Renderer renderer;
};

#endif
