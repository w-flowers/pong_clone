# Pong Clone

## Purpose

This repository contains an engine and a gui to enable one to build a "pong-like" game or simulation. Currently, it contains:

- Code that abstracts the basic primitive objects of balls, lines and points.
- Code that builds these abstractions up into "boundary" and "field" objects, consisting of these primitives.
- Code that detects and computes collisions between balls and lines, points or other balls.
- A "game" class, which builds and advances a field according to the rules defined in the physics class.
- A GUI class which enables the rendering of a field and the primitive game objects.

The engine is called "pong-like" as it adds some extra complexity, in particular, support for multiple balls, angled lines and ball-point collisions.

The code is designed so that it can be reused accross a number of applications. Currently, the only complete application is a ball simulator, the code for which is defined in apps/ballsim/main.cpp. The final goal of this project is to have a working pong game which can be played by two players on the same or different computers.

The structure of the code is designed to follow a rough model-view-controller architecture. Balls, Lines and Boundaries, and to some extent Fields, form the model, upon which the Physics, Field and Game classes act as controllers. The GUI corresponds to the view. There is some blurring between the model and the controller code, in particular in the Field class.

## Components

### Physics

The functions for Physics are defined in inc/physics.hpp and src/physics.cpp, and operate on the objects defined in the line and ball classes. The collision detection functions detect overlapping, while the actual collisions themselves are elastic collisions, i.e. the code assumes that no energy is lost in collision. In the collision algorithm, there is also an anti-clipping mechanism which seperates overlapping objects in order to ensure that the corresponding "collide" methods do not keep being called step after step.

These physics functions could in theory be used without any external framework, however, the field class provides tools to effectively make use of these functions.

### Field and Boundary

The field class stores a collection of balls, boundaries, goals and paddles. It takes responsibility for running collision detection and execution between these objects, and for advancing the world (one step at a time).

To aid this class in doing so, the field is divided into a grid, and references to the field's objects are stored in the grid squares in which they are contained. This grid is then used to reduce the number of collision detection algorithms being run, with collisions only being checked for objects in the same grid square. Each ball has a set of objects which it may collide with stored in a hash map (using the ball's pointer for hashing), duplicate ball collisions are removed, and collisions are checked using the physics functions. The number of squares in the grid can be adjusted, but the squares are uniformly sized.

The boundary class is a simple list of connected edges and goals.

### GUI

Currently based on SDL2, this is the class which creates the window and renders the game objects. Balls are drawn using the midpoint-circle algorithm, and are pre-drawn onto a texture which is then copied to the ball's location.

The GUI class in particular is designed to have a public interface such that internal implementation could be changed to use a different library without affecting other classes.

### Game

The class that implements the game loop. It sets up the game, handles i/o events, calls the field's advance method, and calls the render\_all() function from the gui. Essentially, this class acts as a controller that manages the other objects which do the real work.
