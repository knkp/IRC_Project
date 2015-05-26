#include "Client_Node.h"



void init_node_client(){
  // this function exists soley for the purpose's of testing,
  // normally it will connect only to socket_server and SS will pass
  // it where it needs to go -- Stephen C
  struct CLIENT_CONFIG config;
  config.id = DEFAULT;
  config.eom = EO_MESSAGE;
  config.delim = MESSAGE_DELIMITER;

  connect_to_Authenticator();
  initial_communication(&config);
}

void connect_to_Authenticator(){
  // create socket for authenticator
  authConnection = socket(AF_INET, SOCK_STREAM, 0);

  if(authConnection == -1){
    printf("Could not create auth socket\n");
  }
  // setup configurations for connection to authenticator
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port = htons( SOCKSERV_2_AUTH_PORT );
  // connect to authenticator

  int authC = connect(authConnection, (struct sockaddr *) &server, sizeof(server));
  if(authC < 0){
    printf("authentication failed\n");
    // return 2;
  }


}

void initial_communication(struct CLIENT_CONFIG* configuration){
  bzero(&message, sizeof(message));

  message[0] = configuration->id;
  message[1] = configuration->eom;
    
    int n = send(authConnection, message, sizeof(message), 0);
    
    if(n < 0){
       printf("write failed for some reason error: %d", errno); 
    }
}

int proc_events(){
  return 1;
}

void build_message(){
  
}
