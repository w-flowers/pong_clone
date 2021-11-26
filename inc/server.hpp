
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

class Server
{
public:

   // Starts the server
   run_server();

private:

   game_loop();

   Field field{};
}

#endif

