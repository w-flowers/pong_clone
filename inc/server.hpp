
/*******************************************************************************
* Pong Clone - Server (server.hpp) 
*
* The server which runs the main game - talks to the client via sockets (either
* locally or over the network). In particular, this will run in a seperate
* process (or possibly on a seperate machine) to the client, and will compute
* the movements of the ball objects in the field, while receiving user input
* from the client.
*
* Author: William Flowers
*******************************************************************************/

#ifndef PONG_SERVER

#define PONG_SERVER

#include <optional>

#include "pong_clone_base.hpp"

#include "field.hpp"

#include <unistd.h>

#include <sys/types.h> 

#include <sys/socket.h> 

#include <netinet/in.h> 

#include <netdb.h> 

#include <arpa/inet.h>

#include <cstring>

class Server
{
public:
   // Accepts two connection types - local or net. In case of local, a socket
   // descriptor is passed in by the calling function (it will be created by a
   // call to socketpair prior to forking the process).
   //
   // In the case of a net connection type, the int for the socket descriptor
   // is unused, and the function should be passed a dummy value.
   Server( std::string& connection_type,
           std::optional<int> socket_descriptor,
           struct Configuration& config );

   ~Server();

   // Starts the server
   void run_server();

private:

   int sd {0};

   int new_fd {0};

   Gametype gametype {sim}

   Field field;

   field_position_data fpd {};

   void sim_loop();

   void game_loop();

   void send_field_info();

   int get_client_move( Player p );

   bool is_local {true};

   class ServerInitError {};

   void send_ball_data( int active_sock, ball_pos_data &bpd const );

   void send_line_data( int active_sock, line_pos_data &lpd const );

   void send_data( int active_sock, char *data_to_send, int data_size );
};

#endif

