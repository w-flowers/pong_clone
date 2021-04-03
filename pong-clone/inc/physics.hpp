
/********************************************************************************
* Pong Clone - Physics (physics.hpp) 
*
* File containing the functions and classes making up the physics engine. To be
* populated in order to better seperate concerns in base classes and enable
* implementation of better algorithms.
*
* Author: William Flowers
********************************************************************************/

#ifndef PHYSICS

#define PHYSICS

class Engine
{
public:
   // Detect collisions and take appropriate action
   void detect_collisions(Field field);

private:

   void bounce(Ball& ball, Edge& edge);

#endif

