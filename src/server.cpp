
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

      freeaddrinfo( server_info );
   }

   else
   {
      throw ServerInitError {};
   }
}

void Server::run_server()
{
   struct sockaddr_storage client_addr;

   socklen_t sock_size;

   if( is_local )
   {
      if( gametype == sim )
      {
         sim_loop();
      }

      else if( gametype == multiplayer )
      {
         game_loop();
      }

      close( sd );

      return 0;
   }

   // Set up sockets and await connections from clients
   
   if( listen( sd, 1 ) == -1 )
   {
      std::cerr << "Call to listen failed.\n";
   }

   new_fd = accept( sd,
                    static_cast<struct sockaddr *>( &client_addr ),
                    &sock_size );

   // Send initial field parameters to clients

   // Enter Game Loop

   if( gametype == sim )
   {
      sim_loop();
   }

   else if( gametype == multiplayer )
   {
      game_loop()
   }

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

   int active_sock {0};

   if( is_local )
   {
      active_sock = sd;
   }

   else
   {
      active_sock = new_fd;
   }

   // send data

   // Send size of list of balls
   send_data( active_sock,
              fpd.ball_positions.size(),
              sizeof( fpd.ball_positions.size() ) );

   for( ball_pos_data bpd : fpd.ball_positions )
   {
      send_ball_data( active_sock, bpd );
   }

   // Send size of list of lines
   send_data( active_sock,
              fpd.line_positions.size(),
              sizeof( fpd.line_positions.size() ) );

   for( line_pos_data lpd : fpd.line_positions )
   {
      send_line_data( active_sock, lpd );
   }
}

void Server::send_ball_data( int active_sock, ball_pos_data &bpd const )
{
   int data_size {0};

   char *data_to_send = &bpd.rounded_x;

   data_size = sizeof( bpd.rounded_x );

   send_data( active_sock, data_to_send, data_size );

   data_to_send = &bpd.rounded_y;

   data_size = sizeof( bpd.rounded_y );

   send_data( active_sock, data_to_send, data_size );

   data_to_send = &bpd.radius;

   data_size = sizeof( bpd.radius );

   send_data( active_sock, data_to_send, data_size );
}

void Server::send_line_data( int active_sock, line_pos_data &lpd const )
{
   int data_size {0};

   char *data_to_send = &lpd.p1.x;

   data_size = sizeof( lpd.p1.x );

   send_data( active_sock, data_to_send, data_size );

   data_to_send = &lpd.p1.y;

   data_size = sizeof( lpd.p1.y );

   send_data( active_sock, data_to_send, data_size );

   data_to_send = &lpd.p2.x;

   data_size = sizeof( lpd.p2.x );

   send_data( active_sock, data_to_send, data_size );

   data_to_send = &lpd.p2.y;

   data_size = sizeof( lpd.p2.y );

   send_data( active_sock, data_to_send, data_size );

   switch( lpd.t )
   {
      case edge:
         send_data( active_sock, 'e', 1 );
         break;

      case goal:
         send_data( active_sock, 'g', 1 );
         break;

      case paddle:
         send_data( active_sock, 'p', 1 );
         break;
   }
}

void Server::send_data( int active_sock, char *data_to_send, int data_size )
{
   int rv {0};

   while( data_size && rv != -1 )
   {
      rv = send( active_sock, data_to_send, data_size, 0 );

      data_size -= rv;

      while( rv > 1 )
      {
         data_to_send++;

         rv--;
      }
   }
}

