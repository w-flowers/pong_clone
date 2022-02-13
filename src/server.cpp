
/*******************************************************************************
* Pong Clone - Server (server.cpp) 
*
* The server which runs the main game - talks to the client via sockets (either
* locally or over the network). In particular, this will run in a seperate
* process (or possibly on a seperate machine) to the client, and will compute
* the movements of the ball objects in the field, while receiving user input
* from the client.
*
* Author: William Flowers
*******************************************************************************/

#include "../inc/server.hpp"

const char* port = "3491";

const int collision_grid_rows = 25;

const int collision_grid_columns = 20;

Server::Server( std::string& connection_type,
           std::optional<int> socket_descriptor,
           struct Configuration& config ):
   field { config, collision_grid_rows, collision_grid_columns }
{
   // Section 1 - initialise sd - either using provided descriptor
   // or via calls to unix api
   if( connection_type == "local" )
   {
      if( socket_descriptor.has_value() )
      {
         is_local = true;

         gametype = config.gametype;

         sd = *socket_descriptor;
      }

      else
      {
         std::cerr << "No socket descriptor provided.\n";

         throw ServerInitError {};
      }
   }

   else if( connection_type == "net" )
   {
      // Create socket to listen on
      // Store socket in sd

      is_local = false;

      gametype = config.gametype;

      struct addrinfo hints, *server_info, *a;

      std::memset( &hints, 0, sizeof( hints ) );

      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = AI_PASSIVE;
      hints.ai_protocol = 0;
      hints.ai_canonname = NULL;
      hints.ai_addr = NULL;
      hints.ai_next = NULL;

      if( getaddrinfo( NULL, port, &hints, &server_info ) )
      {
         std::cerr << "Call to getaddrinfo failed.\n";

         throw ServerInitError {};
      }

      for( a = server_info; a != NULL; a = a->ai_next )
      {
         sd = socket( a->ai_family, a->ai_socktype, a->ai_protocol );

         if( sd == -1 )
         {
            continue;
         }

         if( !bind( sd, a->ai_addr, a->ai_addrlen ) )
         {
            break;
         }

         close(sd);
      }

      if( !a )
      {
         std::cerr << "Could not bind.\n";

         throw ServerInitError {};
      }
   }

   else
   {
      throw ServerInitError {};
   }
}

void Server::run_server()
{
   if( is_local )
   // Set up sockets and await connections from clients
   
   // Create field
   
   // Send initial field parameters to clients

   // Enter Game Loop
   
   game_loop();

   // Cleanup resources
}

void Server::sim_loop()
{
   while( 1 )
   {
      field.advance_field();

      send_field_info();

      // Check for quit signal from client
   }

   // Acknowledge quit signal and exit
}

void Server::game_loop()
{
   // Send field state to client

   // Receive inputs from players

   // Advance field
}

void Server::send_field_info()
{
   field.write_field_positions( fpd );

   // send data

   // Send size of list of balls

   for( ball_pos_data bpd : fpd.ball_positions )
   {
      // Send data for each ball
   }

   // Send size of list of lines

   for( line_pos_data lpd : fpd.line_positions )
   {
      // Send data for each line
   }

   fpd.ball_positions.clear();

   fpd.line_positions.clear();
}

