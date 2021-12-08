
/*******************************************************************************
* Pong Clone - Client (client.hpp) 
*
* The client which receives input from the server to update the field position,
* renders this information, and accepts user input to send back to the server.
* This client will run in a seperate process or on a seperate machine to the
* server. A client may be used by 2 players (for a local game), or by one player
* (for a networked game).
*
* Author: William Flowers
*******************************************************************************/

#ifndef PONG_CLIENT

#define PONG_CLIENT

#include "pong_clone_base.hpp"

struct init_client
{
   Player x; //Owner of game - set to none if client is used by two people
};

class Client
{
public:
   Client( init_client ini );

   ~Client();

};

#endif

