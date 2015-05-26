#ifndef CLIENT_NODE_H
#define CLIENT_NODE_H

#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr

//int notQuit = 1;

void init_node_client();
void connect_to_Authenticator();
int proc_events();

#endif
