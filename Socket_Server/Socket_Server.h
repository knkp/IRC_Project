#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <sys/types.h>
#include <string.h>

#define SOCKSERV_2_AUTH_PORT 9001
#define CLIENT_NODE_2_SOCKSERV_PORT 9000

int init_authenticator_connection();
int init_main_handler();
void handle_incoming_connections();

int listeningSocket, incomingConnections, authConnection, c;
struct sockaddr_in server, client;


// pass the incoming socket descriptors to the authenticator
char message[5] = "1234";

#endif
