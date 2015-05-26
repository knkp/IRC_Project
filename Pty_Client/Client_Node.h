#ifndef CLIENT_NODE_H
#define CLIENT_NODE_H

#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<errno.h>

#define SOCKSERV_2_AUTH_PORT 9001
#define DEFAULT 0xFF            // default ID, the client passes this to SOCKET_SERVER indiciating it needs to be authetnicated
#define EO_MESSAGE 0xEE         // message packets are of constant size, thus use this value to indiciate if the content ends early
#define MESSAGE_DELIMITER 0xDD  // for content that must be separated into it's constiutent parts, use this value to split messages (or to indiciate how to split it)

struct CLIENT_CONFIG{
  char id;
  char eom;
  char delim;
};

int listeningSocket, incomingConnections, authConnection, c;
struct sockaddr_in server, client;
char message[200];

void init_node_client();
void connect_to_Authenticator();
void initial_communication(struct CLIENT_CONFIG* config);
int proc_events();

#endif
