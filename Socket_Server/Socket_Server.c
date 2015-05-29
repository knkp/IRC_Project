#include "Socket_Server.h"

int init_authenticator_connection(){
  // create authenticator socket
  // authConnection = socket(AF_INET, SOCK_STREAM, 0);
  // connect to authenticator

  printf("creating a socket authenticator socket\n");

  // create socket for authenticator
  authConnection = socket(AF_INET, SOCK_STREAM, 0);

  if(authConnection == -1){
    printf("Could not create auth socket\n");
    return -1;
  }
  // setup configurations for connection to authenticator
  bzero((char*)&server, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port = htons( SOCKSERV_2_AUTH_PORT );

  // connect to authenticator
  int authC = connect(authConnection, (struct sockaddr *) &server, sizeof(server));
  if(authC < 0){
    printf("authentication failed\n");
    return -1;
  }

  return 0;
}

int init_main_handler(){
  // Create listener socket
  printf("Creating listener socket");

  listeningSocket = socket(AF_INET, SOCK_STREAM, 0);

  if(listeningSocket == -1){
    printf("Could not create socket\n");
    return -1;
  }


  // setup the listen socket for connections from client_nodes
  bzero((char *)&server, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons( CLIENT_NODE_2_SOCKSERV_PORT );

  //Bind
  printf("binding to socket\n");
  if( bind(listeningSocket, (struct socketaddr_in *)&server, sizeof(server)) < 0){
    puts("bind failed");
    return -1;
  }
  puts("bind done");


  // listen
  printf("listening\n");
  listen(listeningSocket, 3);

  //Accept and incoming connection
  puts("Waiting for incoming connections...");
  c = sizeof(struct sockaddr_in);

  return 0;

}

void handle_incoming_connections(){
  incomingConnections = accept(listeningSocket, (struct sockaddr *)&client, (socklen_t*)&c);

  if(incomingConnections<0){
    printf("accept failed");
    return;
  }

  puts("Connection accepted passing to authenticator\n");
  int n = send(authConnection, message, sizeof(message), 0);
  if(n < 0){
    printf("write failed for some reason error: %d", errno);
    return;
  }

}

